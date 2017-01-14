using System;
using System.Windows.Forms;

namespace opf_managed_test
{
    public partial class OPFMenu : Form
    {
        private static OPFBenchmark benchmark_form = null;
        private static OPFVisual visual_form = null;

        public static OPFBenchmark BenchmarkForm
        {
            set
            {
                benchmark_form = value;
            }
        }
        public static OPFVisual VisualForm
        {
            set
            {
                visual_form = value;
            }
        }

        public OPFMenu()
        {
            InitializeComponent();
            base.FormBorderStyle = FormBorderStyle.FixedSingle;
            base.MaximizeBox = false;
            panel_picture.BackgroundImageLayout = ImageLayout.Stretch;
        }

        private void visualPlayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (visual_form == null)
            {
                visual_form = new OPFVisual();
                visual_form.Show();
            }
            else
            {
                visual_form.Focus();
            }
        }
        private void benchmarkToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (benchmark_form == null)
            {
                benchmark_form = new OPFBenchmark();
                benchmark_form.Show();
            }
            else
            {
                benchmark_form.Focus();
            }
        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                System.Diagnostics.Process.Start(@"docs\opf_system_overview.pdf");
            }
            catch (System.ComponentModel.Win32Exception w32e)
            {
                MessageBox.Show(@"docs\opf_system_overview.pdf: " + w32e.Message, "Win32 Exception", MessageBoxButtons.OK, MessageBoxIcon.None);
            }
        }

        private void documentationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            { 
                System.Diagnostics.Process.Start(@"docs\opf_doc.pdf");
            }
            catch (System.ComponentModel.Win32Exception w32e)
            {
                MessageBox.Show(@"docs\opf_doc.pdf: " + w32e.Message, "Win32 Exception", MessageBoxButtons.OK, MessageBoxIcon.None);
            }
        }

        private void creditsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Cygwin, Notepad++
            MessageBox.Show("ANeDe - For the beautiful art piece of Oromë. \n http://anede.deviantart.com/" +
                            "\n\nNetwide Assembler - For providing the assembler.  \n http://www.nasm.us/" +
                            "\n\nCygwin - For providing the gnu bintools on Windows. \n https://www.cygwin.com/" +
                            "\n\nNotepad++ - For providing a no nonsense IDE. \n https://notepad-plus-plus.org/" +
                            "\n\nx64dbg - For providing the best 64-bit alternative to ollydbg. \n http://x64dbg.com/", 
                            "Credits", MessageBoxButtons.OK, MessageBoxIcon.None);
        }

        private void versionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Autor: Jonas Brown" +
                            "\nContact: brown8220@hotmail.com" +
                            "\n\nOromë Pathfinder System: v0.0.5" +
                            "\nOromë Pathfinder NASM Source: v0.3.0",
                            "Version", MessageBoxButtons.OK, MessageBoxIcon.None);
        }
    }
}
