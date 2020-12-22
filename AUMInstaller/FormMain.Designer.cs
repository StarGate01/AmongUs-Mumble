
namespace AUMInstaller
{
    partial class FormMain
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.btnDownload = new System.Windows.Forms.Button();
            this.txtPick = new System.Windows.Forms.Label();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.txtboxFilePath = new System.Windows.Forms.TextBox();
            this.linklblDiscordServer = new System.Windows.Forms.LinkLabel();
            this.linklblSourceCode = new System.Windows.Forms.LinkLabel();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBoxVersion = new System.Windows.Forms.ComboBox();
            this.progressBarInstall = new System.Windows.Forms.ProgressBar();
            this.listBoxLog = new System.Windows.Forms.ListBox();
            this.groupBoxInstall = new System.Windows.Forms.GroupBox();
            this.groupBoxInput = new System.Windows.Forms.GroupBox();
            this.openFileGame = new System.Windows.Forms.OpenFileDialog();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonUninstall = new System.Windows.Forms.Button();
            this.groupBoxInstall.SuspendLayout();
            this.groupBoxInput.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnDownload
            // 
            this.btnDownload.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDownload.Location = new System.Drawing.Point(9, 60);
            this.btnDownload.Name = "btnDownload";
            this.btnDownload.Size = new System.Drawing.Size(117, 23);
            this.btnDownload.TabIndex = 0;
            this.btnDownload.Text = "Install";
            this.btnDownload.UseVisualStyleBackColor = true;
            this.btnDownload.Click += new System.EventHandler(this.btnDownload_Click);
            // 
            // txtPick
            // 
            this.txtPick.AutoSize = true;
            this.txtPick.Location = new System.Drawing.Point(6, 16);
            this.txtPick.Name = "txtPick";
            this.txtPick.Size = new System.Drawing.Size(192, 13);
            this.txtPick.TabIndex = 3;
            this.txtPick.Text = "Select the file path of \"Among Us.exe\":";
            // 
            // btnBrowse
            // 
            this.btnBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnBrowse.Location = new System.Drawing.Point(617, 33);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(75, 21);
            this.btnBrowse.TabIndex = 4;
            this.btnBrowse.Text = "Browse ...";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // txtboxFilePath
            // 
            this.txtboxFilePath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtboxFilePath.Location = new System.Drawing.Point(9, 34);
            this.txtboxFilePath.Name = "txtboxFilePath";
            this.txtboxFilePath.Size = new System.Drawing.Size(602, 20);
            this.txtboxFilePath.TabIndex = 5;
            this.txtboxFilePath.TextChanged += new System.EventHandler(this.txtboxFilePath_TextChanged);
            // 
            // linklblDiscordServer
            // 
            this.linklblDiscordServer.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.linklblDiscordServer.AutoSize = true;
            this.linklblDiscordServer.Location = new System.Drawing.Point(58, 549);
            this.linklblDiscordServer.Name = "linklblDiscordServer";
            this.linklblDiscordServer.Size = new System.Drawing.Size(43, 13);
            this.linklblDiscordServer.TabIndex = 7;
            this.linklblDiscordServer.TabStop = true;
            this.linklblDiscordServer.Text = "Discord";
            this.linklblDiscordServer.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linklblDiscordServer_LinkClicked);
            // 
            // linklblSourceCode
            // 
            this.linklblSourceCode.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.linklblSourceCode.AutoSize = true;
            this.linklblSourceCode.Location = new System.Drawing.Point(12, 549);
            this.linklblSourceCode.Name = "linklblSourceCode";
            this.linklblSourceCode.Size = new System.Drawing.Size(40, 13);
            this.linklblSourceCode.TabIndex = 8;
            this.linklblSourceCode.TabStop = true;
            this.linklblSourceCode.Text = "GitHub";
            this.linklblSourceCode.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linklblSourceCode_LinkClicked);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(159, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Select the version of your game:";
            // 
            // comboBoxVersion
            // 
            this.comboBoxVersion.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxVersion.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxVersion.FormattingEnabled = true;
            this.comboBoxVersion.Location = new System.Drawing.Point(9, 33);
            this.comboBoxVersion.Name = "comboBoxVersion";
            this.comboBoxVersion.Size = new System.Drawing.Size(683, 21);
            this.comboBoxVersion.TabIndex = 10;
            // 
            // progressBarInstall
            // 
            this.progressBarInstall.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.progressBarInstall.Location = new System.Drawing.Point(132, 60);
            this.progressBarInstall.Maximum = 4;
            this.progressBarInstall.Name = "progressBarInstall";
            this.progressBarInstall.Size = new System.Drawing.Size(560, 23);
            this.progressBarInstall.Step = 1;
            this.progressBarInstall.TabIndex = 11;
            // 
            // listBoxLog
            // 
            this.listBoxLog.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listBoxLog.FormattingEnabled = true;
            this.listBoxLog.HorizontalScrollbar = true;
            this.listBoxLog.Location = new System.Drawing.Point(9, 19);
            this.listBoxLog.Name = "listBoxLog";
            this.listBoxLog.SelectionMode = System.Windows.Forms.SelectionMode.None;
            this.listBoxLog.Size = new System.Drawing.Size(683, 303);
            this.listBoxLog.TabIndex = 12;
            // 
            // groupBoxInstall
            // 
            this.groupBoxInstall.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxInstall.Controls.Add(this.buttonUninstall);
            this.groupBoxInstall.Controls.Add(this.label1);
            this.groupBoxInstall.Controls.Add(this.btnDownload);
            this.groupBoxInstall.Controls.Add(this.progressBarInstall);
            this.groupBoxInstall.Controls.Add(this.comboBoxVersion);
            this.groupBoxInstall.Enabled = false;
            this.groupBoxInstall.Location = new System.Drawing.Point(15, 81);
            this.groupBoxInstall.Name = "groupBoxInstall";
            this.groupBoxInstall.Size = new System.Drawing.Size(698, 122);
            this.groupBoxInstall.TabIndex = 13;
            this.groupBoxInstall.TabStop = false;
            this.groupBoxInstall.Text = "Install / Uninstall";
            // 
            // groupBoxInput
            // 
            this.groupBoxInput.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxInput.Controls.Add(this.txtPick);
            this.groupBoxInput.Controls.Add(this.btnBrowse);
            this.groupBoxInput.Controls.Add(this.txtboxFilePath);
            this.groupBoxInput.Location = new System.Drawing.Point(15, 12);
            this.groupBoxInput.Name = "groupBoxInput";
            this.groupBoxInput.Size = new System.Drawing.Size(698, 63);
            this.groupBoxInput.TabIndex = 14;
            this.groupBoxInput.TabStop = false;
            this.groupBoxInput.Text = "Setup";
            // 
            // openFileGame
            // 
            this.openFileGame.DefaultExt = "exe";
            this.openFileGame.FileName = "Among Us.exe";
            this.openFileGame.Filter = "Among Us executable|Among Us.exe";
            this.openFileGame.InitialDirectory = "C:\\\\";
            this.openFileGame.Title = "Select the Among Us executable";
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.listBoxLog);
            this.groupBox1.Location = new System.Drawing.Point(15, 209);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(698, 337);
            this.groupBox1.TabIndex = 15;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Log";
            // 
            // buttonUninstall
            // 
            this.buttonUninstall.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonUninstall.Location = new System.Drawing.Point(9, 89);
            this.buttonUninstall.Name = "buttonUninstall";
            this.buttonUninstall.Size = new System.Drawing.Size(117, 23);
            this.buttonUninstall.TabIndex = 0;
            this.buttonUninstall.Text = "Uninstall";
            this.buttonUninstall.UseVisualStyleBackColor = true;
            this.buttonUninstall.Click += new System.EventHandler(this.buttonUninstall_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(725, 571);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBoxInput);
            this.Controls.Add(this.groupBoxInstall);
            this.Controls.Add(this.linklblSourceCode);
            this.Controls.Add(this.linklblDiscordServer);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(250, 400);
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "AmongUs-Mumble Installer and Updater";
            this.Shown += new System.EventHandler(this.FormMain_Shown);
            this.groupBoxInstall.ResumeLayout(false);
            this.groupBoxInstall.PerformLayout();
            this.groupBoxInput.ResumeLayout(false);
            this.groupBoxInput.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnDownload;
        private System.Windows.Forms.Label txtPick;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.TextBox txtboxFilePath;
        private System.Windows.Forms.LinkLabel linklblDiscordServer;
        private System.Windows.Forms.LinkLabel linklblSourceCode;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBoxVersion;
        private System.Windows.Forms.GroupBox groupBoxInstall;
        private System.Windows.Forms.GroupBox groupBoxInput;
        private System.Windows.Forms.OpenFileDialog openFileGame;
        public System.Windows.Forms.ProgressBar progressBarInstall;
        public System.Windows.Forms.ListBox listBoxLog;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buttonUninstall;
    }
}

