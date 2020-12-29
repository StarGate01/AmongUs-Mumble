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
    public partial class FormMain : Form
    {

        private Logger logger;
        private Installer installer;

        public FormMain()
        {
            InitializeComponent();
            txtboxFilePath.Click += AmongUsFilePathOnClick;
            logger = new Logger(this);
            installer = new Installer(logger);
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

            private void AmongUsFilePathOnClick(object sender, EventArgs eventArgs)
        {
            // Select text on click
            var textBox = (TextBox)sender;
            textBox.SelectAll();
            textBox.Focus();
        }
        private async void FormMain_Shown(object sender, EventArgs e)
        {
            logger.Log("Application started");

            // Find game installation path
            txtboxFilePath.Text = await installer.GetSteamGameLocation();

            // Populate game version selection
            comboBoxVersion.Items.Clear();
            foreach(ModVersion version in await installer.GetModVersions()) 
                comboBoxVersion.Items.Add(version);
            if(comboBoxVersion.Items.Count > 0) comboBoxVersion.SelectedIndex = 0;
        }

        private void txtboxFilePath_TextChanged(object sender, EventArgs e)
        {
            // Enable install option only if selected file exists
            groupBoxInstall.Enabled = File.Exists(txtboxFilePath.Text);
        }

        private async void btnDownload_Click(object sender, EventArgs e)
        {
            logger.Log("Starting installation");
            logger.Reset();
            groupBoxInput.Enabled = false;

            // Disable install button
            btnDownload.Text = "Installing...";
            btnDownload.Enabled = false;

            // Install VC redist
            await installer.InstallVCRedist();
            
            // Install mod
            if(comboBoxVersion.SelectedItem != null)
            {
                string gameDir = Path.GetDirectoryName(txtboxFilePath.Text);
                await installer.InstallMod(gameDir, (ModVersion)comboBoxVersion.SelectedItem);
            }
            else
            {
                logger.Log("No game version selected.");
                logger.CompleteStep(2);
            }

            groupBoxInput.Enabled = true;

            // Re-enable install button
            btnDownload.Text = "Install";
            btnDownload.Enabled = true;

            MessageBox.Show(this, "Installation finished. Check the log for details.", 
                "Installation finished", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void buttonUninstall_Click(object sender, EventArgs e)
        {
            logger.Log("Starting uninstallation");
            logger.Reset();
            groupBoxInput.Enabled = false;

            string gameDir = Path.GetDirectoryName(txtboxFilePath.Text);
            installer.UninstallMod(gameDir);

            groupBoxInput.Enabled = true;

            MessageBox.Show(this, "Uninstallation finished. Check the log for details.",
                "Uninstallation finished", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            // Display the open file dialog
            DialogResult res = openFileGame.ShowDialog(this);
            if(res == DialogResult.OK)
            {
                txtboxFilePath.Text = openFileGame.FileName;
            }
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

    
    }
}
