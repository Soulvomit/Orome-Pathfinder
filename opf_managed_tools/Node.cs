using opf_managed_win_wrapper;
using System.Drawing;
using System.Windows.Forms;

namespace opf_managed_test
{
    public class Node: Control, IPFVector
    {
        ushort[] coordinates;
        byte traversable;
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

        public byte Traversable
        {
            get
            {
                return traversable;
            }
            set
            {
                if (value >= 1)
                {
                    this.BackColor = originColor;
                    this.traversable = 1;
                }
                else if (value <= 0)
                {
                    this.BackColor = Color.LightSlateGray;
                    this.traversable = 0;
                }
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
            Traversable = 1;
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
                if (this.traversable >= 1)
                {
                    Traversable = 0;
                }
                else if (this.traversable <= 0)
                {
                    Traversable = 1;
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
