namespace opf_managed_test
{
    partial class OPFMenu
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(OPFMenu));
            this.ms_opf = new System.Windows.Forms.MenuStrip();
            this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.benchmarkToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.visualPlayToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.infoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.documentationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.versionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.creditsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel_picture = new System.Windows.Forms.Panel();
            this.ms_opf.SuspendLayout();
            this.SuspendLayout();
            // 
            // ms_opf
            // 
            this.ms_opf.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ms_opf.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolsToolStripMenuItem,
            this.infoToolStripMenuItem});
            this.ms_opf.Location = new System.Drawing.Point(0, 0);
            this.ms_opf.Name = "ms_opf";
            this.ms_opf.Padding = new System.Windows.Forms.Padding(7, 2, 0, 2);
            this.ms_opf.Size = new System.Drawing.Size(537, 24);
            this.ms_opf.TabIndex = 14;
            this.ms_opf.Text = "ms_opf";
            // 
            // toolsToolStripMenuItem
            // 
            this.toolsToolStripMenuItem.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.toolsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.benchmarkToolStripMenuItem,
            this.visualPlayToolStripMenuItem});
            this.toolsToolStripMenuItem.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold);
            this.toolsToolStripMenuItem.ForeColor = System.Drawing.SystemColors.ControlText;
            this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
            this.toolsToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.toolsToolStripMenuItem.Text = "Tools";
            // 
            // benchmarkToolStripMenuItem
            // 
            this.benchmarkToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlText;
            this.benchmarkToolStripMenuItem.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.benchmarkToolStripMenuItem.Name = "benchmarkToolStripMenuItem";
            this.benchmarkToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
            this.benchmarkToolStripMenuItem.Text = "Benchmark";
            this.benchmarkToolStripMenuItem.Click += new System.EventHandler(this.benchmarkToolStripMenuItem_Click);
            // 
            // visualPlayToolStripMenuItem
            // 
            this.visualPlayToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlText;
            this.visualPlayToolStripMenuItem.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.visualPlayToolStripMenuItem.Name = "visualPlayToolStripMenuItem";
            this.visualPlayToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
            this.visualPlayToolStripMenuItem.Text = "Visual Play";
            this.visualPlayToolStripMenuItem.Click += new System.EventHandler(this.visualPlayToolStripMenuItem_Click);
            // 
            // infoToolStripMenuItem
            // 
            this.infoToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.documentationToolStripMenuItem,
            this.helpToolStripMenuItem,
            this.versionToolStripMenuItem,
            this.creditsToolStripMenuItem});
            this.infoToolStripMenuItem.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold);
            this.infoToolStripMenuItem.ForeColor = System.Drawing.SystemColors.ControlText;
            this.infoToolStripMenuItem.Name = "infoToolStripMenuItem";
            this.infoToolStripMenuItem.Size = new System.Drawing.Size(41, 20);
            this.infoToolStripMenuItem.Text = "Info";
            // 
            // documentationToolStripMenuItem
            // 
            this.documentationToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlText;
            this.documentationToolStripMenuItem.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.documentationToolStripMenuItem.Name = "documentationToolStripMenuItem";
            this.documentationToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.documentationToolStripMenuItem.Text = "Documentation";
            this.documentationToolStripMenuItem.Click += new System.EventHandler(this.documentationToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlText;
            this.helpToolStripMenuItem.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.helpToolStripMenuItem.Text = "System Overview";
            this.helpToolStripMenuItem.Click += new System.EventHandler(this.helpToolStripMenuItem_Click);
            // 
            // versionToolStripMenuItem
            // 
            this.versionToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlText;
            this.versionToolStripMenuItem.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.versionToolStripMenuItem.Name = "versionToolStripMenuItem";
            this.versionToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.versionToolStripMenuItem.Text = "Version";
            this.versionToolStripMenuItem.Click += new System.EventHandler(this.versionToolStripMenuItem_Click);
            // 
            // creditsToolStripMenuItem
            // 
            this.creditsToolStripMenuItem.BackColor = System.Drawing.SystemColors.ControlText;
            this.creditsToolStripMenuItem.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.creditsToolStripMenuItem.Name = "creditsToolStripMenuItem";
            this.creditsToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.creditsToolStripMenuItem.Text = "Credits";
            this.creditsToolStripMenuItem.Click += new System.EventHandler(this.creditsToolStripMenuItem_Click);
            // 
            // panel_picture
            // 
            this.panel_picture.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("panel_picture.BackgroundImage")));
            this.panel_picture.Location = new System.Drawing.Point(12, 39);
            this.panel_picture.Name = "panel_picture";
            this.panel_picture.Size = new System.Drawing.Size(513, 260);
            this.panel_picture.TabIndex = 15;
            // 
            // OPFMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlText;
            this.ClientSize = new System.Drawing.Size(537, 311);
            this.Controls.Add(this.panel_picture);
            this.Controls.Add(this.ms_opf);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.Name = "OPFMenu";
            this.ShowIcon = false;
            this.Text = "OROMË PATHFINDER";
            this.ms_opf.ResumeLayout(false);
            this.ms_opf.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip ms_opf;
        private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem benchmarkToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem visualPlayToolStripMenuItem;
        private System.Windows.Forms.Panel panel_picture;
        private System.Windows.Forms.ToolStripMenuItem infoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem documentationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem versionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem creditsToolStripMenuItem;
    }
}