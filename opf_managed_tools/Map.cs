using opf_managed_win_wrapper;
using System.Diagnostics;
using System.Drawing;

namespace opf_managed_test
{
    public class Map: IOPFMap
    {
        private Node[,] grid;
        private ushort width;
        private ushort height;
        private int size;
        private OPFVisual pfTester;
        private Node startNode = null;
        private Node targetNode = null;
        private int[] currentPath = null;

        #region Properties
        public Node[,] Grid
        {
            get
            {
                return grid;
            }
        }
        public ushort Height
        {
            get
            {
                return height;
            }
        }

        public ushort Width
        {
            get
            {
                return width;
            }
        }
        public Node StartNode
        {
            get
            {
                return startNode;
            }
            set
            {
                if (startNode != null)
                {
                    startNode.BackColor = startNode.OriginColor;
                }
                if (currentPath != null)
                {
                    HidePath(currentPath);
                    currentPath = null;
                }
                startNode = value;
                startNode.Traversable = 1;
                startNode.BackColor = Color.Magenta;
            }
        }
        public Node TargetNode
        {
            get
            {
                return targetNode;
            }
            set
            {
                targetNode = value;
            }
        }
        #endregion

        public Map(ushort width, ushort height, int size, OPFVisual pfTester, int margainHeight)
        {
            this.width = width;
            this.height = height;
            this.size = size;
            this.pfTester = pfTester;

            grid = new Node[width, height];

            int counter = 0;
            for (ushort y = 0; y < height; y++)
            {
                for (ushort x = 0; x < width; x++)
                {
                    grid[x, y] = new Node(x, y, pfTester, counter.ToString(), x * size, (y * size) + margainHeight, size, size, DetColor(x, y));
                    counter++;
                }
            }
        }

        public void FindPath()
        {
            if (currentPath != null)
            {
                HidePath(currentPath);
            }

            Stopwatch sw = new Stopwatch();
            sw.Start();
            PFTask pft = new PFTask(startNode, targetNode, this, width*height, OPFVisual.IncludeDiagonals, 1);
            pft.WaitJoin();
            sw.Stop();

            if (pft.PathLength > 0)
            {
                OPFVisual.Console.Text = "CONSOLE::Length="+pft.PathLength+", Time=" + (sw.Elapsed.TotalMilliseconds * 1000000) + "ns";
                currentPath = pft.FinalPath;
                ShowPath(currentPath);
            }
            else
            {
                OPFVisual.Console.Text = "CONSOLE::" + pft.Status;
            }
        }
        public void ClearPath()
        {
            if (startNode != null)
            {
                startNode.BackColor = startNode.OriginColor;
                startNode = null;
            }
            if (currentPath != null)
            {
                HidePath(currentPath);
                currentPath = null;
            }
        }

        public byte[] GetLinearTopography()
        {
            byte[] linearTopography = new byte[width * height];
            int counter = 0;
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    linearTopography[counter] = Grid[x,y].Traversable;
                    counter++;
                }
            }
            return linearTopography;
        }

        private void ShowPath(int[] path)
        {
            for(int index = 0; index < path.Length; index++)
            {
                int x = path[index] % width;
                int y = path[index] / width;
                Grid[x, y].BackColor = Color.Red;
            }
        }

        private void HidePath(int[] path)
        {
            for (int index = 0; index < path.Length; index++)
            {
                int x = path[index] % width;
                int y = path[index] / width;
                Grid[x, y].BackColor = Grid[x, y].OriginColor;
            }
        }    

        private Color DetColor(int x, int y)
        {
            if (y % 2 == 0)
            {
                if (x % 2 == 0)
                {
                    return Color.Cyan;
                }
                else
                {
                    return Color.Aquamarine;
                }
            }
            else
            {
                if (x % 2 == 0)
                {
                    return Color.Aquamarine;
                }
                else
                {
                    return Color.Cyan;
                }
            }
        }
    }
}
