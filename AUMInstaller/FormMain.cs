using System;
using System.Net;
using System.IO;
using System.Diagnostics;
using Microsoft.Win32;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AUMInstaller
{
    public partial class ModInstaller : Form
    {
        public string modversion;
        public string moddownload;
        public string gameversion;
        public ModInstaller(string downloadLink, string modVersion, string gameVersion)
        {
            InitializeComponent();
            modversion = modVersion;
            moddownload = downloadLink;
            gameversion = gameVersion;
            txtboxFilePath.Click += TextBoxOnClick;
        }
        private string BrowseFilePath()
        {
            FolderBrowserDialog folderDlg = new FolderBrowserDialog();
            folderDlg.ShowNewFolderButton = false;
            DialogResult result = folderDlg.ShowDialog();
            if (result == DialogResult.OK)
            {
                return folderDlg.SelectedPath;
            }
            else
            {
                return txtboxFilePath.Text;
            }
        }
        private WebClient webClient = null;
        private void btnDownload_Click(object sender, EventArgs e)
        {

            string sixtyfourbit = "https://aka.ms/vs/16/release/vc_redist.x64.exe";
            string thirtytwobit = "https://aka.ms/vs/16/release/vc_redist.x86.exe";

            // Checks if file path exists
            if (!Directory.Exists(txtboxFilePath.Text))
            {
                MessageBox.Show("Please put a valid file location\n\nOne way to find the file loaction is to go to Steam and right click on Among Us in your library and do \"Manage\" then \"Browse Local Files\"");
                txtboxFilePath.Text = BrowseFilePath();
            }
            else
            {
                btnDownload.Text = "Installing...";
                btnDownload.Enabled = false;
                // Windows redistributable
                if (webClient != null)
                    return;
                webClient = new WebClient();

                if (Environment.Is64BitOperatingSystem)
                {
                    // Download 64bit
                    webClient.DownloadFile(new Uri(sixtyfourbit), txtboxFilePath.Text + "runtime.exe");
                }
                else
                {
                    // Download 32bit
                    webClient.DownloadFile(new Uri(thirtytwobit), txtboxFilePath.Text + "runtime.exe");
                }
                webClient = null;

                // Run runtime.exe
                Process runtimeProcess = new Process();
                runtimeProcess.StartInfo.FileName = txtboxFilePath.Text + "runtime.exe";
                runtimeProcess.StartInfo.Arguments = " /install /quiet /norestart";
                runtimeProcess.Start();
                // Delete
                File.Delete(Path.Combine(txtboxFilePath.Text, "runtime.exe"));

                // Checks if mod already exists, if not then its then deleted
                if (File.Exists(Path.Combine(txtboxFilePath.Text, "winhttp.dll")))
                {
                    File.Delete(Path.Combine(txtboxFilePath.Text, "winhttp.dll"));
                }

                if (webClient != null)
                    return;

                webClient = new WebClient();
                webClient.DownloadFile(new Uri(moddownload), txtboxFilePath.Text + modversion);
                webClient = null;

                // Unzip mod
                string startPath = txtboxFilePath.Text + modversion;
                string zipPath = txtboxFilePath.Text + modversion;
                string extractPath = txtboxFilePath.Text;
                System.IO.Compression.ZipFile.ExtractToDirectory(zipPath, extractPath);

                // Delete mod zip file
                File.Delete(txtboxFilePath.Text + modversion);

                btnDownload.Text = "Install";
                btnDownload.Enabled = true;
                
                // Download Complete!
                MessageBox.Show("Downloaded Latest Release: " + modversion + "\n\nCompatible game version: " + gameversion + "\n\nTo file location: " + txtboxFilePath.Text + "\n\nMake sure that it downloaded to the same file lacation as \"Among Us.exe\"\n\nIf you have any issues we can help you in our Discord server!");
            }
        }
        private void btnBrowse_Click(object sender, EventArgs e)
        {
            txtboxFilePath.Text = BrowseFilePath();
        }

        private void linklblOldModVersions_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            // Specify that the link was visited
            this.linklblOldModVersions.LinkVisited = true;

            // Navigate to a URL
            System.Diagnostics.Process.Start("https://github.com/StarGate01/AmongUs-Mumble#amongus-mumble");
        }

        private void linklblDiscordServer_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            // Specify that the link was visited
            this.linklblDiscordServer.LinkVisited = true;

            // Navigate to a URL
            System.Diagnostics.Process.Start("https://discord.gg/4UkHEJ5sqg");
        }
        private void linklblSourceCode_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            // Specify that the link was visited
            this.linklblSourceCode.LinkVisited = true;

            // Navigate to a URL
            System.Diagnostics.Process.Start("https://github.com/StarGate01/AmongUs-Mumble/");
        }
        private void TextBoxOnClick(object sender, EventArgs eventArgs)
        {
            // Select text on click
            var textBox = (TextBox)sender;
            textBox.SelectAll();
            textBox.Focus();
        }
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            // Esc button closes program
            if (keyData == Keys.Escape)
            {
                this.Close();
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
    }
}
