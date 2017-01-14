using System;
using System.Windows.Forms;

namespace opf_managed_test
{
    public partial class OPFBenchmark : Form
    {
        public OPFBenchmark()
        {
            InitializeComponent();

            base.FormBorderStyle = FormBorderStyle.FixedSingle;
            base.MaximizeBox = false;
            base.MinimizeBox = false;
        }

        private void btn_benchmark_Click(object sender, EventArgs e)
        {
            int width = (int)nud_width.Value;
            int height = (int)nud_height.Value;
            int max_pathlength = (int)nud_max_pathlength.Value;
            int passes = (int)nud_passes.Value;
            int activethreads = tb_activethreads.Value;
            int frequency = tb_frequency.Value;

            string args = width + " " + height + " " + max_pathlength + " " + passes + " " +
                          activethreads + " " + frequency;
            try
            { 
                System.Diagnostics.Process.Start("opf_native_test.exe", args);
            }
            catch (System.ComponentModel.Win32Exception w32e)
            {
                MessageBox.Show("opf_native_test.exe: " + w32e.Message, "Win32 Exception", MessageBoxButtons.OK, MessageBoxIcon.None);
            }
        }

        private void tb_activethreads_Scroll(object sender, EventArgs e)
        {
            lbl_activethreads.Text = "Active Threads: " + tb_activethreads.Value;
        }

        private void tb_frequency_Scroll(object sender, EventArgs e)
        {
            if (tb_frequency.Value == 26)
            {
                lbl_frequency.Text = "Tiles per Block: NO BLOCKS";
            }
            else
            {
                lbl_frequency.Text = "Tiles per Block: " + tb_frequency.Value;
            }
        }

        private void OPFBenchmark_FormClosed(object sender, FormClosedEventArgs e)
        {
            OPFMenu.BenchmarkForm = null;
        }
    }
}
