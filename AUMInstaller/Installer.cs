using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;
using Microsoft.Win32;
using System.Text.RegularExpressions;
using System.IO.Compression;

namespace AUMInstaller
{

    class ModVersion
    {

        public string gameVersion;

        public string modVersion;

        public string zipDownload;

        public override string ToString()
        {
            return gameVersion + " (Mod version " + modVersion + ")";
        }

    }

    class Installer
    {

        private Logger logger;

        public Installer(Logger log)
        {
            logger = log;
        }

        public async Task<string> GetSteamGameLocation()
        {
            // Run this in a new task to not lag the UI
            return await Task.Run(() =>
            {
                logger.Log("Detecting Steam game installation path");

                // Find steam installtion directory in registry
                string regKey = (Environment.Is64BitOperatingSystem) ?
                    @"SOFTWARE\Wow6432Node\Valve\Steam" : @"SOFTWARE\Valve\Steam";
                logger.Log("Looking up registry key " + regKey);
                using (RegistryKey key = Registry.LocalMachine.OpenSubKey(regKey))
                {
                    if (key != null)
                    {
                        object o = key.GetValue("InstallPath");
                        if (o != null)
                        {
                            string steamInstall = (string)o;
                            logger.Log("Found Steam installation at " + steamInstall);

                            // Build a list containing all local steam library locations
                            List<string> steamLibs = new List<string>() { steamInstall + @"\steamapps" };
                            string libFoldersFile = steamInstall + @"\steamapps\libraryfolders.vdf";
                            if (File.Exists(libFoldersFile))
                            {
                                logger.Log("Reading Steam library file " + libFoldersFile);
                                string libContent = File.ReadAllText(libFoldersFile);

                                // Parse the library file
                                foreach (Match match in Regex.Matches(libContent,
                                    "^\\s*\"[0-9]+\"\\s*\"(.*)\"\\s*$", RegexOptions.Multiline))
                                {
                                    if (match.Groups.Count == 2)
                                        steamLibs.Add(match.Groups[1].Value.Replace(@"\\", @"\") + @"\steamapps");
                                }
                            }
                            logger.Log("Found Steam libraries: " + string.Join(", ", steamLibs));

                            // Search for game in all libraries
                            foreach (string libDir in steamLibs)
                            {
                                string appMan = libDir + @"\appmanifest_945360.acf";
                                if (File.Exists(appMan))
                                {
                                    logger.Log("Found game application manifest at " + appMan);
                                    string gamePath = libDir + @"\common\Among Us\Among Us.exe";
                                    logger.Log("Game executable should be located at " + gamePath);
                                    return gamePath;
                                }
                            }
                        }
                    }
                    else
                    {
                        logger.Log("Failed to read registry key " + regKey);
                    }
                }
                return string.Empty;
            });
        }

        public async Task<List<ModVersion>> GetModVersions()
        {
            logger.Log("Downloading list of available mod versions");
            List<ModVersion> versions = new List<ModVersion>();

            // Download the version wiki page
            using (WebClient wc = new WebClient())
            {
                string downloadUrl = @"https://raw.githubusercontent.com/wiki/StarGate01/AmongUs-Mumble/Versions.md";
                try
                {
                    string readmeText = await wc.DownloadStringTaskAsync(downloadUrl);

                    // Parse the version table in the readme
                    foreach (Match match in Regex.Matches(readmeText,
                        "^\\|\\s*([^-]*?)\\s*\\|(?:.*?\\|){2}\\s*\\[(.*)\\].*$", RegexOptions.Multiline))
                    {
                        if (match.Groups.Count == 3)
                        {
                            string modVersion = match.Groups[2].Value;
                            versions.Add(new ModVersion()
                            {
                                gameVersion = match.Groups[1].Value,
                                modVersion = modVersion,
                                zipDownload = @"https://github.com/StarGate01/AmongUs-Mumble/releases/download/v" +
                                    modVersion + "/AmongUs-Mumble-" + modVersion + ".zip"
                            });
                        }
                    }
                }
                catch (Exception e)
                {
                    // Download failed
                    logger.Log("Failed to download " + downloadUrl + ", reason: " + e.Message);
                    logger.CompleteStep(2);
                    logger.Log("Failed to download list of available mod versions");
                }
            }

            logger.Log("Found " + versions.Count().ToString() + " available versions");
            return versions;
        }

        public async Task InstallVCRedist()
        {
            logger.Log("Installing Visual C++ 2015 redistributable");
            string localFileName = Path.GetTempFileName().Replace(".tmp", ".exe");
            using (WebClient wc = new WebClient())
            {
                // Download redist installer, we only need 32 bit
                string downloadUrl = "https://aka.ms/vs/16/release/vc_redist.x86.exe";
                logger.Log("Starting download of " + downloadUrl);
                try
                {
                    await wc.DownloadFileTaskAsync(downloadUrl, localFileName);
                    logger.Log("Finished downloading " + downloadUrl);
                    logger.CompleteStep();

                    // Execute installer
                    logger.Log("Launching VC redist installer " + localFileName);
                    Process rp = new Process
                    {
                        StartInfo = { FileName = localFileName, Arguments = " /install /silent /norestart" },
                        EnableRaisingEvents = true
                    };
                    var tcs = new TaskCompletionSource<int>();
                    rp.Exited += (object sender, EventArgs e) =>
                    {
                        tcs.SetResult(rp.ExitCode);
                        rp.Dispose();
                    };
                    rp.Start();
                    int exitCode = await tcs.Task;
                    logger.Log("VC redist installer finished, exit code " + exitCode.ToString());
                    logger.CompleteStep();

                    // Cleanup
                    File.Delete(localFileName);
                    logger.Log("Successfully installed Visual C++ 2015 redistributable");
                }
                catch (Exception e)
                {
                    // Download failed
                    logger.Log("Failed to download " + downloadUrl + ", reason: " + e.Message);
                    logger.CompleteStep(2);
                    logger.Log("Failed to install Visual C++ 2015 redistributable");
                }
            }
        }

        public async Task InstallMod(string gameDirectory, ModVersion version)
        {
            logger.Log("Installing mod version " + version.modVersion + " to " + gameDirectory);
            string localFileName = Path.GetTempFileName().Replace(".tmp", ".zip");
            using (WebClient wc = new WebClient())
            {
                // Download mod zip file
                logger.Log("Starting download of " + version.zipDownload);
                try
                {
                    await wc.DownloadFileTaskAsync(version.zipDownload, localFileName);
                    logger.Log("Finished downloading " + version.zipDownload);
                    logger.CompleteStep();

                    try
                    {
                        // Rename old version if it is installed
                        if (File.Exists(gameDirectory + @"\winhttp.dll"))
                        {
                            if (File.Exists(gameDirectory + @"\winhttp.dll.old"))
                            {
                                logger.Log("Deleting previous winhttp.dll.old");
                                File.Delete(gameDirectory + @"\winhttp.dll.old");
                            }
                            logger.Log("Renaming old existing winhttp.dll to winhttp.dll.old");
                            File.Move(gameDirectory + @"\winhttp.dll", gameDirectory + @"\winhttp.dll.old");
                        }

                        // Unpack mod
                        logger.Log("Unpacking mod zip file " + localFileName);
                        ZipFile.ExtractToDirectory(localFileName, gameDirectory);
                        logger.Log("Successfully installed mod");
                    }
                    catch (Exception e)
                    {
                        // Unpacking failed
                        logger.Log("Failed to unpack " + localFileName + ", reason: " + e.Message);
                        logger.Log("Failed to install mod");
                    }
                    logger.CompleteStep();

                    // Cleanup
                    File.Delete(localFileName);
                }
                catch (Exception e)
                {
                    // Download failed
                    logger.Log("Failed to download " + version.zipDownload + ", reason: " + e.Message);
                    logger.CompleteStep(2);
                    logger.Log("Failed to install mod");
                }
            }
        }

        public void UninstallMod(string gameDirectory)
        {
            logger.Log("Uninstalling mod from " + gameDirectory);
            if (File.Exists(gameDirectory + @"\winhttp.dll"))
            {
                File.Delete(gameDirectory + @"\winhttp.dll");
                logger.Log("Removed " + gameDirectory + @"\winhttp.dll");
            }
            if (File.Exists(gameDirectory + @"\winhttp.dll.old"))
            {
                File.Delete(gameDirectory + @"\winhttp.dll.old");
                logger.Log("Removed " + gameDirectory + @"\winhttp.dll.old");
            }
            logger.Log("Successfully uninstalled mod");
            logger.CompleteStep(4);
        }

    }
}
