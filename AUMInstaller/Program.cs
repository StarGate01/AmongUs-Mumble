using System;
using Newtonsoft.Json.Linq;
using System.IO;
using System.IO.Compression;
using System.Net;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace AUMInstaller
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            WebClient wb = new WebClient();
            wb.Headers.Add("User-Agent: Other");
            string jsonString = wb.DownloadString("https://api.github.com/repos/StarGate01/AmongUs-Mumble/releases/latest");

            dynamic response = JObject.Parse(jsonString);
            string downloadLink = response.assets[0].browser_download_url;
            string modVersion = response.tag_name;
            string thebodytext = response.body;

            string gameVersion;
            Match match = Regex.Match(thebodytext, @"game version: \*\*(.+)\*\*");
            if (match.Success)
            {
                gameVersion = match.Groups[1].Value;
            }
            else
            {
                // Failed to find the verison
                gameVersion = "unknown";
            }
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new ModInstaller(downloadLink, modVersion, gameVersion));
        }
    }
}
