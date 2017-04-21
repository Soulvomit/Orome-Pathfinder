using System;
using System.Drawing;
using System.Windows.Forms;

namespace opf_managed_test
{
    public enum FillStatus
    {
        ORIGIN,
        BLOCK
    }
    public partial class OPFVisual : Form
    {
        private static FillStatus fillstatus = FillStatus.ORIGIN;
        private static Map map = null;
        private static Label lbl_console;
        private static CheckBox cb_include_diag;
        private static CheckBox cb_use_failsafe;

        public static FillStatus FillStatus
        {
            get
            {
                return fillstatus;
            }
        }
        public static Label Console
        {
            get
            {
                return lbl_console;
            }
        }
        public static bool IncludeDiagonals
        {
            get
            {
                return cb_include_diag.Checked;
            }
        }
        public static bool UseFailsafe
        {
            get
            {
                return cb_use_failsafe.Checked;
            }
        }
        public static Map Map
        {
            get
            {
                return map;
            }
        }

        public OPFVisual()
        {
            InitializeComponent();

            lbl_console = new System.Windows.Forms.Label();
            base.Controls.Add(lbl_console);
            lbl_console.AutoSize = true;
            lbl_console.Font = new System.Drawing.Font("Lucida Console", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            lbl_console.Name = "Console";
            lbl_console.Size = new System.Drawing.Size(0, 10);
            lbl_console.Visible = false;
            lbl_console.ForeColor = Color.Red;
            lbl_console.Text = "CONSOLE::Place Origin";
            lbl_console.Top = 5;
            lbl_console.Left = 5;

            rbtn_origin.Top = 18;
            rbtn_origin.Left = 5;
            rbtn_block.Top = 33;
            rbtn_block.Left = 5;
            rbtn_origin.Checked = true;

            cb_include_diag = new System.Windows.Forms.CheckBox();
            base.Controls.Add(cb_include_diag);
            cb_include_diag.AutoSize = true;
            cb_include_diag.Checked = true;
            cb_include_diag.CheckState = System.Windows.Forms.CheckState.Checked;
            cb_include_diag.Name = "cb_include_diag";
            cb_include_diag.Size = new System.Drawing.Size(128, 17);
            cb_include_diag.TabIndex = 13;
            cb_include_diag.Text = "Include Diagonals";
            cb_include_diag.UseVisualStyleBackColor = true;
            cb_include_diag.Visible = false;
            cb_include_diag.Top = 33;
            cb_include_diag.Left = 150;
            cb_include_diag.Checked = true;

            cb_use_failsafe = new System.Windows.Forms.CheckBox();
            base.Controls.Add(cb_use_failsafe);
            cb_use_failsafe.AutoSize = true;
            cb_use_failsafe.Checked = true;
            cb_use_failsafe.CheckState = System.Windows.Forms.CheckState.Checked;
            cb_use_failsafe.Name = "cb_use_failsafe";
            cb_use_failsafe.Size = new System.Drawing.Size(128, 17);
            cb_use_failsafe.TabIndex = 13;
            cb_use_failsafe.Text = "Use Failsafe";
            cb_use_failsafe.UseVisualStyleBackColor = true;
            cb_use_failsafe.Visible = false;
            cb_use_failsafe.Top = 18;
            cb_use_failsafe.Left = 150;
            cb_use_failsafe.Checked = false;

            base.FormBorderStyle = FormBorderStyle.FixedSingle;
            base.MaximizeBox = false;
            base.MinimizeBox = false;
        }

        private void ToggleStartLayout()
        {
            tb_width.Visible = !tb_width.Visible;
            tb_height.Visible = !tb_height.Visible;
            tb_size.Visible = !tb_size.Visible;
            lbl_width.Visible = !lbl_width.Visible;
            lbl_height.Visible = !lbl_height.Visible;
            lbl_size.Visible = !lbl_size.Visible;
            tb_frequency.Visible = !tb_frequency.Visible;
            lbl_frequency.Visible = !lbl_frequency.Visible;
            btn_creategrid.Visible = !btn_creategrid.Visible;

            //map items
            rbtn_origin.Visible = !rbtn_origin.Visible;
            rbtn_block.Visible = !rbtn_block.Visible;
            lbl_console.Visible = !lbl_console.Visible;
            cb_include_diag.Visible = !cb_include_diag.Visible;
            cb_use_failsafe.Visible = !cb_use_failsafe.Visible;
        }
        private Map InitMap()
        {
            int topMarginWidth = 335;
            int topMarginHeight = 50;
            int Width = tb_width.Value;
            int Height = tb_height.Value;
            int Size = tb_size.Value;
            this.Width = Width * Size + 15;
            //add width if the space is to small
            if (topMarginWidth > this.Width)
            {
                this.Width = topMarginWidth;
            }
            this.Height = Height * Size + 39 + topMarginHeight;
            ToggleStartLayout();
            return new Map((ushort)Width, (ushort)Height, Size, this, topMarginHeight);
        }

        private void btn_creategrid_Click(object sender, System.EventArgs e)
        {
            Map tempMap = InitMap();
            //randomize
            if (tb_frequency.Value < 11)
            {
                Random rand = new Random();
                foreach (Node n in tempMap.Grid)
                {
                    if (rand.Next(tb_frequency.Value) == 0)
                    {
                        n.Traversable = 0;
                    }
                }
            }
            else if (tb_frequency.Value == 11)
            {
                //tempMap.GenerateMaze();
            }
            map = tempMap;
        }

        private void tb_width_Scroll(object sender, System.EventArgs e)
        {
            lbl_width.Text = "Map Width: " + tb_width.Value;
        }

        private void tb_height_Scroll(object sender, System.EventArgs e)
        {
            lbl_height.Text = "Map Height: " + tb_height.Value;
        }

        private void tb_size_Scroll(object sender, System.EventArgs e)
        {
            lbl_size.Text = "Node Size: " + tb_size.Value;
        }

        private void tb_frequency_Scroll(object sender, EventArgs e)
        {
            if (tb_frequency.Value == 11)
            {
                lbl_frequency.Text = "Tiles per Block: NONE";
            }
            else
            {
                lbl_frequency.Text = "Tiles per Block: " + tb_frequency.Value;
            }
        }

        private void rbtn_origin_CheckedChanged(object sender, EventArgs e)
        {
            lbl_console.Text = "CONSOLE::Place Origin";
            fillstatus = FillStatus.ORIGIN;
        }

        private void rbtn_block_CheckedChanged(object sender, EventArgs e)
        {
            lbl_console.Text = "CONSOLE::Place/Remove Blocks";
            map.ClearPath();
            fillstatus = FillStatus.BLOCK;
        }

        private void OPFVisual_FormClosed(object sender, FormClosedEventArgs e)
        {
            OPFMenu.VisualForm = null;
        }
    }
}
