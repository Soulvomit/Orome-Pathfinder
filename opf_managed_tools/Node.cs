using opf_managed_win_wrapper;
using System.Drawing;
using System.Windows.Forms;
using System;

namespace opf_managed_test
{
    public class Node: Control, IOPFVector
    {
        ushort[] coordinates;
        bool traversable;
        Color originColor;

        #region Properties
        public Color OriginColor
        {
            get
            {
                return originColor;
            }
        }
        public ushort IntX
        {
            get
            {
                return this.coordinates[0];
            }
        }

        public ushort IntY
        {
            get
            {
                return this.coordinates[1];
            }
        }

        public bool Traversable
        {
            get
            {
                return traversable;
            }
            set
            {
                if (value == true)
                {
                    this.BackColor = originColor;
                }
                else
                {
                    this.BackColor = Color.LightSlateGray;
                }
                this.traversable = value;
            }
        }

        public byte Resistance
        {
            get
            {
                throw new NotImplementedException();
            }
        }
        #endregion

        public Node(ushort x, ushort y, Control parent, string text, int left, int top, int width, int height, Color color): 
            base(parent, text, left, top, width, height)
        {
            InitializeComponent();
            this.coordinates = new ushort[2];
            this.coordinates[0] = x;
            this.coordinates[1] = y;
            this.originColor = color;
            Traversable = true;
        }

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // Node
            // 
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Node_MouseDown);
            this.MouseEnter += new System.EventHandler(this.Node_MouseEnter);
            this.ResumeLayout(false);

        }

        private void Node_MouseDown(object sender, MouseEventArgs e)
        {

            if (OPFVisual.FillStatus == FillStatus.BLOCK)
            {
                if (!this.traversable)
                {
                    Traversable = false;
                }
                else
                {
                    Traversable = true;
                }
            }
            else if (OPFVisual.FillStatus == FillStatus.ORIGIN)
            {
                OPFVisual.Map.StartNode = this;    
            }
        }

        private void Node_MouseEnter(object sender, System.EventArgs e)
        {
            if (OPFVisual.Map.StartNode != null && OPFVisual.FillStatus == FillStatus.ORIGIN)
            {
                OPFVisual.Map.TargetNode = this;
                OPFVisual.Map.FindPath();
            }
        }
    }
}
