namespace opf_managed_test
{
    partial class OPFBenchmark
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
            this.btn_benchmark = new System.Windows.Forms.Button();
            this.nud_width = new System.Windows.Forms.NumericUpDown();
            this.nud_height = new System.Windows.Forms.NumericUpDown();
            this.nud_max_pathlength = new System.Windows.Forms.NumericUpDown();
            this.lbl_width = new System.Windows.Forms.Label();
            this.lbl_height = new System.Windows.Forms.Label();
            this.lbl_max_pathlength = new System.Windows.Forms.Label();
            this.lbl_passes = new System.Windows.Forms.Label();
            this.nud_passes = new System.Windows.Forms.NumericUpDown();
            this.lbl_activethreads = new System.Windows.Forms.Label();
            this.lbl_frequency = new System.Windows.Forms.Label();
            this.tb_frequency = new System.Windows.Forms.TrackBar();
            this.tb_activethreads = new System.Windows.Forms.TrackBar();
            this.cb_threaded = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.nud_width)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_height)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_max_pathlength)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_passes)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_frequency)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_activethreads)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_benchmark
            // 
            this.btn_benchmark.BackColor = System.Drawing.SystemColors.ControlText;
            this.btn_benchmark.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_benchmark.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.btn_benchmark.Location = new System.Drawing.Point(120, 275);
            this.btn_benchmark.Name = "btn_benchmark";
            this.btn_benchmark.Size = new System.Drawing.Size(93, 23);
            this.btn_benchmark.TabIndex = 14;
            this.btn_benchmark.Text = "Benchmark";
            this.btn_benchmark.UseVisualStyleBackColor = false;
            this.btn_benchmark.Click += new System.EventHandler(this.btn_benchmark_Click);
            // 
            // nud_width
            // 
            this.nud_width.BackColor = System.Drawing.SystemColors.ControlText;
            this.nud_width.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.nud_width.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nud_width.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.nud_width.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nud_width.Location = new System.Drawing.Point(148, 14);
            this.nud_width.Maximum = new decimal(new int[] {
            50000,
            0,
            0,
            0});
            this.nud_width.Minimum = new decimal(new int[] {
            64,
            0,
            0,
            0});
            this.nud_width.Name = "nud_width";
            this.nud_width.Size = new System.Drawing.Size(65, 16);
            this.nud_width.TabIndex = 15;
            this.nud_width.Value = new decimal(new int[] {
            4000,
            0,
            0,
            0});
            // 
            // nud_height
            // 
            this.nud_height.BackColor = System.Drawing.SystemColors.ControlText;
            this.nud_height.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.nud_height.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nud_height.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.nud_height.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nud_height.Location = new System.Drawing.Point(148, 39);
            this.nud_height.Maximum = new decimal(new int[] {
            50000,
            0,
            0,
            0});
            this.nud_height.Minimum = new decimal(new int[] {
            64,
            0,
            0,
            0});
            this.nud_height.Name = "nud_height";
            this.nud_height.Size = new System.Drawing.Size(65, 16);
            this.nud_height.TabIndex = 16;
            this.nud_height.Value = new decimal(new int[] {
            4000,
            0,
            0,
            0});
            // 
            // nud_max_pathlength
            // 
            this.nud_max_pathlength.BackColor = System.Drawing.SystemColors.ControlText;
            this.nud_max_pathlength.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.nud_max_pathlength.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nud_max_pathlength.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.nud_max_pathlength.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nud_max_pathlength.Location = new System.Drawing.Point(148, 65);
            this.nud_max_pathlength.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.nud_max_pathlength.Minimum = new decimal(new int[] {
            128,
            0,
            0,
            0});
            this.nud_max_pathlength.Name = "nud_max_pathlength";
            this.nud_max_pathlength.Size = new System.Drawing.Size(65, 16);
            this.nud_max_pathlength.TabIndex = 17;
            this.nud_max_pathlength.Value = new decimal(new int[] {
            8000,
            0,
            0,
            0});
            // 
            // lbl_width
            // 
            this.lbl_width.AutoSize = true;
            this.lbl_width.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_width.Location = new System.Drawing.Point(12, 13);
            this.lbl_width.Name = "lbl_width";
            this.lbl_width.Size = new System.Drawing.Size(79, 13);
            this.lbl_width.TabIndex = 18;
            this.lbl_width.Text = "MAP WIDTH";
            // 
            // lbl_height
            // 
            this.lbl_height.AutoSize = true;
            this.lbl_height.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_height.Location = new System.Drawing.Point(12, 38);
            this.lbl_height.Name = "lbl_height";
            this.lbl_height.Size = new System.Drawing.Size(84, 13);
            this.lbl_height.TabIndex = 19;
            this.lbl_height.Text = "MAP HEIGHT";
            // 
            // lbl_max_pathlength
            // 
            this.lbl_max_pathlength.AutoSize = true;
            this.lbl_max_pathlength.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_max_pathlength.Location = new System.Drawing.Point(12, 64);
            this.lbl_max_pathlength.Name = "lbl_max_pathlength";
            this.lbl_max_pathlength.Size = new System.Drawing.Size(120, 13);
            this.lbl_max_pathlength.TabIndex = 20;
            this.lbl_max_pathlength.Text = "MAX PATHLENGTH";
            // 
            // lbl_passes
            // 
            this.lbl_passes.AutoSize = true;
            this.lbl_passes.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_passes.Location = new System.Drawing.Point(12, 90);
            this.lbl_passes.Name = "lbl_passes";
            this.lbl_passes.Size = new System.Drawing.Size(55, 13);
            this.lbl_passes.TabIndex = 21;
            this.lbl_passes.Text = "PASSES";
            // 
            // nud_passes
            // 
            this.nud_passes.BackColor = System.Drawing.SystemColors.ControlText;
            this.nud_passes.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.nud_passes.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nud_passes.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.nud_passes.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nud_passes.Location = new System.Drawing.Point(148, 91);
            this.nud_passes.Maximum = new decimal(new int[] {
            999999,
            0,
            0,
            0});
            this.nud_passes.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nud_passes.Name = "nud_passes";
            this.nud_passes.Size = new System.Drawing.Size(65, 16);
            this.nud_passes.TabIndex = 22;
            this.nud_passes.Value = new decimal(new int[] {
            25,
            0,
            0,
            0});
            // 
            // lbl_activethreads
            // 
            this.lbl_activethreads.AutoSize = true;
            this.lbl_activethreads.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_activethreads.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.lbl_activethreads.Location = new System.Drawing.Point(12, 120);
            this.lbl_activethreads.Name = "lbl_activethreads";
            this.lbl_activethreads.Size = new System.Drawing.Size(108, 13);
            this.lbl_activethreads.TabIndex = 23;
            this.lbl_activethreads.Text = "Active Threads: 4";
            // 
            // lbl_frequency
            // 
            this.lbl_frequency.AutoSize = true;
            this.lbl_frequency.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_frequency.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.lbl_frequency.Location = new System.Drawing.Point(12, 184);
            this.lbl_frequency.Name = "lbl_frequency";
            this.lbl_frequency.Size = new System.Drawing.Size(107, 13);
            this.lbl_frequency.TabIndex = 24;
            this.lbl_frequency.Text = "Tiles per Block: 6";
            // 
            // tb_frequency
            // 
            this.tb_frequency.Location = new System.Drawing.Point(12, 200);
            this.tb_frequency.Maximum = 26;
            this.tb_frequency.Minimum = 2;
            this.tb_frequency.Name = "tb_frequency";
            this.tb_frequency.Size = new System.Drawing.Size(201, 45);
            this.tb_frequency.TabIndex = 25;
            this.tb_frequency.Value = 6;
            this.tb_frequency.Scroll += new System.EventHandler(this.tb_frequency_Scroll);
            // 
            // tb_activethreads
            // 
            this.tb_activethreads.Location = new System.Drawing.Point(12, 136);
            this.tb_activethreads.Maximum = 16;
            this.tb_activethreads.Minimum = 1;
            this.tb_activethreads.Name = "tb_activethreads";
            this.tb_activethreads.Size = new System.Drawing.Size(201, 45);
            this.tb_activethreads.TabIndex = 26;
            this.tb_activethreads.Value = 4;
            this.tb_activethreads.Scroll += new System.EventHandler(this.tb_activethreads_Scroll);
            // 
            // cb_threaded
            // 
            this.cb_threaded.AutoSize = true;
            this.cb_threaded.Checked = true;
            this.cb_threaded.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cb_threaded.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cb_threaded.Location = new System.Drawing.Point(15, 251);
            this.cb_threaded.Name = "cb_threaded";
            this.cb_threaded.Size = new System.Drawing.Size(80, 17);
            this.cb_threaded.TabIndex = 27;
            this.cb_threaded.Text = "Threaded";
            this.cb_threaded.UseVisualStyleBackColor = true;
            this.cb_threaded.CheckedChanged += new System.EventHandler(this.cb_threaded_CheckedChanged);
            // 
            // OPFBenchmark
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlText;
            this.ClientSize = new System.Drawing.Size(225, 310);
            this.Controls.Add(this.cb_threaded);
            this.Controls.Add(this.tb_activethreads);
            this.Controls.Add(this.tb_frequency);
            this.Controls.Add(this.lbl_frequency);
            this.Controls.Add(this.lbl_activethreads);
            this.Controls.Add(this.nud_passes);
            this.Controls.Add(this.lbl_passes);
            this.Controls.Add(this.lbl_max_pathlength);
            this.Controls.Add(this.lbl_height);
            this.Controls.Add(this.lbl_width);
            this.Controls.Add(this.nud_max_pathlength);
            this.Controls.Add(this.nud_height);
            this.Controls.Add(this.nud_width);
            this.Controls.Add(this.btn_benchmark);
            this.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.Name = "OPFBenchmark";
            this.ShowIcon = false;
            this.Text = "OPF BENCHMARK";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.OPFBenchmark_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.nud_width)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_height)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_max_pathlength)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_passes)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_frequency)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tb_activethreads)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_benchmark;
        private System.Windows.Forms.NumericUpDown nud_width;
        private System.Windows.Forms.NumericUpDown nud_height;
        private System.Windows.Forms.NumericUpDown nud_max_pathlength;
        private System.Windows.Forms.Label lbl_width;
        private System.Windows.Forms.Label lbl_height;
        private System.Windows.Forms.Label lbl_max_pathlength;
        private System.Windows.Forms.Label lbl_passes;
        private System.Windows.Forms.NumericUpDown nud_passes;
        private System.Windows.Forms.Label lbl_activethreads;
        private System.Windows.Forms.Label lbl_frequency;
        private System.Windows.Forms.TrackBar tb_frequency;
        private System.Windows.Forms.TrackBar tb_activethreads;
        private System.Windows.Forms.CheckBox cb_threaded;
    }
}