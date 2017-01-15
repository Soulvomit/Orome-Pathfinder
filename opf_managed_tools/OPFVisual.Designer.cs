namespace opf_managed_test
{
    partial class OPFVisual
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
            this.btn_creategrid = new System.Windows.Forms.Button();
            this.tb_width = new System.Windows.Forms.TrackBar();
            this.tb_height = new System.Windows.Forms.TrackBar();
            this.tb_size = new System.Windows.Forms.TrackBar();
            this.lbl_width = new System.Windows.Forms.Label();
            this.lbl_height = new System.Windows.Forms.Label();
            this.lbl_size = new System.Windows.Forms.Label();
            this.tb_frequency = new System.Windows.Forms.TrackBar();
            this.lbl_frequency = new System.Windows.Forms.Label();
            this.rbtn_origin = new System.Windows.Forms.RadioButton();
            this.rbtn_block = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.tb_width)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_height)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_size)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_frequency)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_creategrid
            // 
            this.btn_creategrid.BackColor = System.Drawing.SystemColors.ControlText;
            this.btn_creategrid.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_creategrid.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.btn_creategrid.Location = new System.Drawing.Point(120, 277);
            this.btn_creategrid.Name = "btn_creategrid";
            this.btn_creategrid.Size = new System.Drawing.Size(93, 23);
            this.btn_creategrid.TabIndex = 1;
            this.btn_creategrid.Text = "Create Map";
            this.btn_creategrid.UseVisualStyleBackColor = false;
            this.btn_creategrid.Click += new System.EventHandler(this.btn_creategrid_Click);
            // 
            // tb_width
            // 
            this.tb_width.Location = new System.Drawing.Point(10, 34);
            this.tb_width.Maximum = 64;
            this.tb_width.Minimum = 5;
            this.tb_width.Name = "tb_width";
            this.tb_width.Size = new System.Drawing.Size(203, 45);
            this.tb_width.TabIndex = 2;
            this.tb_width.Value = 32;
            this.tb_width.Scroll += new System.EventHandler(this.tb_width_Scroll);
            // 
            // tb_height
            // 
            this.tb_height.Location = new System.Drawing.Point(10, 98);
            this.tb_height.Maximum = 64;
            this.tb_height.Minimum = 5;
            this.tb_height.Name = "tb_height";
            this.tb_height.Size = new System.Drawing.Size(203, 45);
            this.tb_height.TabIndex = 3;
            this.tb_height.Value = 32;
            this.tb_height.Scroll += new System.EventHandler(this.tb_height_Scroll);
            // 
            // tb_size
            // 
            this.tb_size.Location = new System.Drawing.Point(12, 162);
            this.tb_size.Maximum = 15;
            this.tb_size.Minimum = 5;
            this.tb_size.Name = "tb_size";
            this.tb_size.Size = new System.Drawing.Size(201, 45);
            this.tb_size.TabIndex = 4;
            this.tb_size.Value = 10;
            this.tb_size.Scroll += new System.EventHandler(this.tb_size_Scroll);
            // 
            // lbl_width
            // 
            this.lbl_width.AutoSize = true;
            this.lbl_width.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_width.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.lbl_width.Location = new System.Drawing.Point(12, 18);
            this.lbl_width.Name = "lbl_width";
            this.lbl_width.Size = new System.Drawing.Size(90, 13);
            this.lbl_width.TabIndex = 5;
            this.lbl_width.Text = "Map Width: 32";
            // 
            // lbl_height
            // 
            this.lbl_height.AutoSize = true;
            this.lbl_height.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_height.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.lbl_height.Location = new System.Drawing.Point(12, 82);
            this.lbl_height.Name = "lbl_height";
            this.lbl_height.Size = new System.Drawing.Size(94, 13);
            this.lbl_height.TabIndex = 6;
            this.lbl_height.Text = "Map Height: 32";
            // 
            // lbl_size
            // 
            this.lbl_size.AutoSize = true;
            this.lbl_size.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_size.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.lbl_size.Location = new System.Drawing.Point(12, 146);
            this.lbl_size.Name = "lbl_size";
            this.lbl_size.Size = new System.Drawing.Size(78, 13);
            this.lbl_size.TabIndex = 7;
            this.lbl_size.Text = "Tile Size: 10";
            // 
            // tb_frequency
            // 
            this.tb_frequency.Location = new System.Drawing.Point(9, 226);
            this.tb_frequency.Maximum = 11;
            this.tb_frequency.Minimum = 2;
            this.tb_frequency.Name = "tb_frequency";
            this.tb_frequency.Size = new System.Drawing.Size(204, 45);
            this.tb_frequency.TabIndex = 8;
            this.tb_frequency.Value = 2;
            this.tb_frequency.Scroll += new System.EventHandler(this.tb_frequency_Scroll);
            // 
            // lbl_frequency
            // 
            this.lbl_frequency.AutoSize = true;
            this.lbl_frequency.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_frequency.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.lbl_frequency.Location = new System.Drawing.Point(12, 210);
            this.lbl_frequency.Name = "lbl_frequency";
            this.lbl_frequency.Size = new System.Drawing.Size(107, 13);
            this.lbl_frequency.TabIndex = 9;
            this.lbl_frequency.Text = "Tiles per Block: 2";
            // 
            // rbtn_origin
            // 
            this.rbtn_origin.AutoSize = true;
            this.rbtn_origin.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rbtn_origin.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.rbtn_origin.Location = new System.Drawing.Point(10, 282);
            this.rbtn_origin.Name = "rbtn_origin";
            this.rbtn_origin.Size = new System.Drawing.Size(94, 17);
            this.rbtn_origin.TabIndex = 10;
            this.rbtn_origin.TabStop = true;
            this.rbtn_origin.Text = "Place Origin";
            this.rbtn_origin.UseVisualStyleBackColor = true;
            this.rbtn_origin.Visible = false;
            this.rbtn_origin.CheckedChanged += new System.EventHandler(this.rbtn_origin_CheckedChanged);
            // 
            // rbtn_block
            // 
            this.rbtn_block.AutoSize = true;
            this.rbtn_block.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rbtn_block.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.rbtn_block.Location = new System.Drawing.Point(9, 265);
            this.rbtn_block.Name = "rbtn_block";
            this.rbtn_block.Size = new System.Drawing.Size(145, 17);
            this.rbtn_block.TabIndex = 12;
            this.rbtn_block.TabStop = true;
            this.rbtn_block.Text = "Place/Remove Block";
            this.rbtn_block.UseVisualStyleBackColor = true;
            this.rbtn_block.Visible = false;
            this.rbtn_block.CheckedChanged += new System.EventHandler(this.rbtn_block_CheckedChanged);
            // 
            // OPFVisual
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlText;
            this.ClientSize = new System.Drawing.Size(225, 310);
            this.Controls.Add(this.rbtn_block);
            this.Controls.Add(this.rbtn_origin);
            this.Controls.Add(this.lbl_frequency);
            this.Controls.Add(this.tb_frequency);
            this.Controls.Add(this.lbl_size);
            this.Controls.Add(this.lbl_height);
            this.Controls.Add(this.lbl_width);
            this.Controls.Add(this.tb_size);
            this.Controls.Add(this.tb_height);
            this.Controls.Add(this.tb_width);
            this.Controls.Add(this.btn_creategrid);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.Name = "OPFVisual";
            this.ShowIcon = false;
            this.Text = "OPF VISUAL PLAY";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.OPFVisual_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.tb_width)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_height)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_size)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_frequency)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion
        private System.Windows.Forms.Button btn_creategrid;
        private System.Windows.Forms.TrackBar tb_width;
        private System.Windows.Forms.TrackBar tb_height;
        private System.Windows.Forms.TrackBar tb_size;
        private System.Windows.Forms.Label lbl_width;
        private System.Windows.Forms.Label lbl_height;
        private System.Windows.Forms.Label lbl_size;
        private System.Windows.Forms.TrackBar tb_frequency;
        private System.Windows.Forms.Label lbl_frequency;
        private System.Windows.Forms.RadioButton rbtn_origin;
        private System.Windows.Forms.RadioButton rbtn_block;
    }
}

