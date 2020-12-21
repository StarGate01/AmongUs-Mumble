
namespace HelloWorld
{
    partial class ModInstaller
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ModInstaller));
            this.btnDownload = new System.Windows.Forms.Button();
            this.txtPick = new System.Windows.Forms.Label();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.txtboxFilePath = new System.Windows.Forms.TextBox();
            this.linklblOldModVersions = new System.Windows.Forms.LinkLabel();
            this.linklblDiscordServer = new System.Windows.Forms.LinkLabel();
            this.linklblSourceCode = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // btnDownload
            // 
            this.btnDownload.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.btnDownload.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDownload.Location = new System.Drawing.Point(163, 54);
            this.btnDownload.Name = "btnDownload";
            this.btnDownload.Size = new System.Drawing.Size(75, 23);
            this.btnDownload.TabIndex = 0;
            this.btnDownload.Text = "Install";
            this.btnDownload.UseVisualStyleBackColor = true;
            this.btnDownload.Click += new System.EventHandler(this.btnDownload_Click);
            // 
            // txtPick
            // 
            this.txtPick.AutoSize = true;
            this.txtPick.Location = new System.Drawing.Point(2, 7);
            this.txtPick.Name = "txtPick";
            this.txtPick.Size = new System.Drawing.Size(248, 13);
            this.txtPick.TabIndex = 3;
            this.txtPick.Text = "Pick the file path where \"Among Us.exe\" is located";
            // 
            // btnBrowse
            // 
            this.btnBrowse.Location = new System.Drawing.Point(313, 24);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(75, 23);
            this.btnBrowse.TabIndex = 4;
            this.btnBrowse.Text = "Browse";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // txtboxFilePath
            // 
            this.txtboxFilePath.Location = new System.Drawing.Point(5, 26);
            this.txtboxFilePath.Name = "txtboxFilePath";
            this.txtboxFilePath.Size = new System.Drawing.Size(302, 20);
            this.txtboxFilePath.TabIndex = 5;
            this.txtboxFilePath.Text = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Among Us";
            // 
            // linklblOldModVersions
            // 
            this.linklblOldModVersions.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.linklblOldModVersions.AutoSize = true;
            this.linklblOldModVersions.Location = new System.Drawing.Point(318, 65);
            this.linklblOldModVersions.Name = "linklblOldModVersions";
            this.linklblOldModVersions.Size = new System.Drawing.Size(75, 13);
            this.linklblOldModVersions.TabIndex = 6;
            this.linklblOldModVersions.TabStop = true;
            this.linklblOldModVersions.Text = "Older Versions";
            this.linklblOldModVersions.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linklblOldModVersions_LinkClicked);
            // 
            // linklblDiscordServer
            // 
            this.linklblDiscordServer.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.linklblDiscordServer.AutoSize = true;
            this.linklblDiscordServer.Location = new System.Drawing.Point(349, 52);
            this.linklblDiscordServer.Name = "linklblDiscordServer";
            this.linklblDiscordServer.Size = new System.Drawing.Size(43, 13);
            this.linklblDiscordServer.TabIndex = 7;
            this.linklblDiscordServer.TabStop = true;
            this.linklblDiscordServer.Text = "Discord";
            this.linklblDiscordServer.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linklblDiscordServer_LinkClicked);
            // 
            // linklblSourceCode
            // 
            this.linklblSourceCode.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.linklblSourceCode.AutoSize = true;
            this.linklblSourceCode.Location = new System.Drawing.Point(323, 3);
            this.linklblSourceCode.Name = "linklblSourceCode";
            this.linklblSourceCode.Size = new System.Drawing.Size(69, 13);
            this.linklblSourceCode.TabIndex = 8;
            this.linklblSourceCode.TabStop = true;
            this.linklblSourceCode.Text = "Source Code";
            this.linklblSourceCode.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linklblSourceCode_LinkClicked);
            // 
            // ModInstaller
            // 
            this.AcceptButton = this.btnDownload;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(394, 86);
            this.Controls.Add(this.linklblSourceCode);
            this.Controls.Add(this.linklblDiscordServer);
            this.Controls.Add(this.linklblOldModVersions);
            this.Controls.Add(this.txtboxFilePath);
            this.Controls.Add(this.btnBrowse);
            this.Controls.Add(this.txtPick);
            this.Controls.Add(this.btnDownload);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(410, 125);
            this.MinimumSize = new System.Drawing.Size(410, 125);
            this.Name = "ModInstaller";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Proximity Mod Installer/Updater";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnDownload;
        private System.Windows.Forms.Label txtPick;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.TextBox txtboxFilePath;
        private System.Windows.Forms.LinkLabel linklblOldModVersions;
        private System.Windows.Forms.LinkLabel linklblDiscordServer;
        private System.Windows.Forms.LinkLabel linklblSourceCode;
    }
}

