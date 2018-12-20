using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    public enum CellType
    {
        Wall,
        Running,
        Rest,
        Dropping
    }

    class WaterBlock : Coord
    {
        public WaterBlock(char display = '~')
        {
            c = display;
        }

        private char c { get; set; }
        public char Display
        {
            get
            {
                if (IsDropping)
                    return '|';
                else if (AtRest)
                    return '~';
                else if (IsRunning)
                    return '^';
                else return '?';
            }
        }

        public CellType Type { get; set; }
        public bool IsDropping
        {
            get
            {
                return (Type == CellType.Dropping);
            }
        }
        public bool AtRest
        {
            get
            {
                return (Type == CellType.Rest);
            }
        }
        public bool IsRunning
        {
            get
            {
                return (Type == CellType.Running);
            }
        }
    }

    class Day17
    {
        List<Coord> clay;
        int xmin;
        int xmax;
        int ymin;
        int ymax;
        List<WaterBlock> water;

        char[,] ground;

        public int LoopCounter { get; set; }
        public int Width { get; set; }
        public int Height { get; set; }

        bool[,] flowhandled;

        public Day17()
        {
            clay = new List<Coord>();
            LoopCounter = 0;
            xmin = ymin = Int32.MaxValue;
            xmax = ymax = Int32.MinValue;

            water = new List<WaterBlock>();
            water.Add(new WaterBlock('+') { x = 500, y = 0, Type = CellType.Dropping });
        }

        public void Part1()
        {
            // Part 1 - ANSWER SHOULD BE 38409
            //
            // Part 2 - ANSWER SHOULD BE 32288
            //
            //x = 495, y = 2..7
            //y = 7, x = 495..501
            //x = 501, y = 3..7
            //x = 498, y = 2..4
            //x = 506, y = 1..2
            //x = 498, y = 10..13
            //x = 504, y = 10..13
            //y = 13, x = 498..504

            string[] lines = System.IO.File.ReadAllLines(@"..\..\day17.txt");
            //string[] lines = System.IO.File.ReadAllLines(@"..\..\d17test.txt");

            foreach (var line in lines)
            {
                var split = line.Split(',');
                var p1split = split[0].Split('=');
                var p2split = split[1].Split('=');

                int xstart = 0, xend = 0, ystart = 0, yend = 0;

                if (p1split[0].Trim() == "x")
                {
                    var nums = p1split[1].Split('.');
                    xstart = xend = Int32.Parse(nums[0]);
                    if (nums.Count() > 1)
                    {
                        xend = Int32.Parse(nums[2]);
                    }
                }
                else
                {
                    var nums = p1split[1].Split('.');
                    ystart = yend = Int32.Parse(nums[0]);
                    if (nums.Count() > 1)
                    {
                        yend = Int32.Parse(nums[2]);
                    }
                }

                if (p2split[0].Trim() == "x")
                {
                    var nums = p2split[1].Split('.');
                    xstart = xend = Int32.Parse(nums[0]);
                    if (nums.Count() > 1)
                    {
                        xend = Int32.Parse(nums[2]);
                    }
                }
                else
                {
                    var nums = p2split[1].Split('.');
                    ystart = yend = Int32.Parse(nums[0]);
                    if (nums.Count() > 1)
                    {
                        yend = Int32.Parse(nums[2]);
                    }
                }

                for (int y = ystart; y <= yend; y++)
                {
                    for (int x = xstart; x <= xend; x++)
                    {
                        clay.Add(new Coord() { x = x, y = y });
                    }
                }

                if (xstart < xmin)
                    xmin = xstart;
                if (xend > xmax)
                    xmax = xend;

                if (ystart < ymin)
                    ymin = ystart;
                if (yend > ymax)
                    ymax = yend;
            }

            // Add some additional x values in case flow goes beyond clay x max
            xmax += 10;
            InitGround();

            Console.WriteLine("xmax {0}   ymax {1}   xmin {2}   ymin {3}", xmax, ymax, xmin, ymin);
            flowhandled = new bool[xmax + 1, ymax + 1];
            for (int y = 0; y <= ymax; y++)
            {
                for (int x = 0; x <= xmax; x++)
                {
                    flowhandled[x, y] = false;
                }
            }

            Fill(500, 0);

            Console.WriteLine("Created {0} water cells", water.Count() - ymin);
            Console.WriteLine("Resting water cells = {0}", water.Count(u=>u.Type == CellType.Rest));
            //Draw();
            CompressWater();
            WriteToFile();
        }

        private void Fill(int x, int y)
        {
            if (x > xmax || y > ymax)
                return;
            if (flowhandled[x, y] == true)
                return;
            flowhandled[x, y] = true;

            int yhit = HitCheck(x, y);
            if (yhit > ymax)
                return;

            yhit--;
            while (true)
            {
                int xl = 0;
                int xr = 0;
                CellType left = ScanRow(x, yhit, -1, ref xl);
                CellType right = ScanRow(x, yhit, 1, ref xr);

                if (left == CellType.Wall && right == CellType.Wall)
                {
                    for (int i = xl + 1; i < xr; i++)
                    {
                        WaterBlock w = water.Find(u => u.x == i && u.y == yhit);
                        if (w == null)
                        {
                            w = new WaterBlock() { x = i, y = yhit, Type = CellType.Rest };
                            ground[w.x, w.y] = w.Display;
                            water.Add(w);
                        }
                        else
                        {
                            w = water.Find(u => u.x == i && u.y == yhit);
                            w.Type = CellType.Rest;
                            ground[w.x, w.y] = w.Display;
                        }
                    }
                }
                else
                {
                    for (int i = xl + 1; i < xr; i++)
                    {
                        WaterBlock w = water.Find(u => u.x == i && u.y == yhit);
                        if (w == null)
                        {
                            w = new WaterBlock() { x = i, y = yhit, Type = CellType.Running };
                            ground[w.x, w.y] = w.Display;
                            water.Add(w);
                        }
                        else
                        {
                            w = water.Find(u => u.x == i && u.y == yhit);
                            w.Type = CellType.Running;
                            ground[w.x, w.y] = w.Display;
                        }
                    }
                    if (left == CellType.Dropping)
                        Fill(xl, yhit);

                    if (right == CellType.Dropping)
                        Fill(xr, yhit);
                    break;
                }
                yhit--;
                if (yhit > ymax)
                    break;
            }
        }

        private int HitCheck(int x, int y)
        {
            while (true)
            {
                if (ground[x, y] == '#')
                    return y;
                if (ground[x, y] == '~' && water.Find(u => u.x == x && u.y == y).AtRest)
                    return y;

                var w = water.Find(u => u.x == x && u.y == y);
                if (w == null)
                {
                    w = new WaterBlock() { x = x, y = y, Type = CellType.Running };
                    ground[w.x, w.y] = w.Display;
                    water.Add(w);
                }
                else
                {
                    w.Type = CellType.Running;
                    ground[w.x, w.y] = w.Display;
                }

                y++;
                if (y > ymax)
                    return ymax;
            }
        }

        private CellType ScanRow(int x, int y, int dir, ref int xval)
        {
            while (true)
            {
                if (ground[x, y] == '#')
                {
                    xval = x;
                    return CellType.Wall;
                }
                else if (ground[x, y + 1] != '#' && (water.Find(u => u.x == x && u.y == y + 1) == null || !water.Find(u => u.x == x && u.y == y + 1).AtRest))
                {
                    xval = x;
                    return CellType.Dropping;
                }
                x += dir;
            }
        }

        private void InitGround()
        {
            Width = xmax + 10;
            Height = ymax + 10;

            ground = new char[Width, Height];
            for (int y = 0; y < Height; y++)
            {
                for (int x = 0; x < Width; x++)
                {
                    ground[x, y] = '.';
                }
            }

            foreach (var item in clay)
            {
                ground[item.x, item.y] = '#';
            }
        }

        private void WriteToFile()
        {
            Console.Write("Writing file day17output.xls");

            char[,] display = new char[Width, Height];
            for (int y = 0; y < Height; y++)
            {
                for (int x = xmin; x < Width; x++)
                {
                    display[x, y] = ground[x, y];
                }
            }

            string output = string.Empty;

            using (System.IO.StreamWriter file =
            new System.IO.StreamWriter(@"day17output.xls"))
            {
                for (int y = 0; y < Height; y++)
                {
                    output = string.Empty;
                    for (int x = xmin; x < Width; x++)
                    {
                        output += display[x, y];
                        output += '\t';
                    }
                    if (y == ymin)
                        output += "<== YMIN";
                    if (y == ymax)
                        output += "<<== YMAX";
                    file.WriteLine(output);
                }
            }
            Console.WriteLine("...Finished");
        }

        public void Draw(int ymin, int ymax)
        {
            Console.Clear();

            for (int y = ymin; y < ymax; y++)
            {
                for (int x = xmin - 10; x < Width; x++)
                {
                    Console.Write(ground[x, y]);
                }
                if (y == 0) Console.Write("Loop {0} ", LoopCounter);

                if (y == ymin)
                    Console.Write("  <<== YMIN");
                if (y == ymax)
                    Console.Write("  <<== YMAX");
                Console.WriteLine();
            }
        }

        public void Draw()
        {
            Console.Clear();

            for (int y = 0; y < Height; y++)
            {
                for (int x = xmin - 10; x < Width; x++)
                {
                    Console.Write(ground[x, y]);
                }
                if (y == 0) Console.Write("Loop {0} ", LoopCounter);

                if (y == ymin)
                    Console.Write("  <<== YMIN");
                if (y == ymax)
                    Console.Write("  <<== YMAX");
                Console.WriteLine();
            }
        }
        private void CompressWater()
        {
            List<WaterBlock> duplicates = new List<WaterBlock>();
            var running = water.FindAll(u => u.IsRunning);
            foreach (var item in running.OrderBy(u => u.y))
            {
                //Console.WriteLine("{0},{1}", item.x, item.y);
                if (water.FindAll(u => u.x == item.x && u.y == item.y).Count() != 1)
                {
                    if (!duplicates.Contains(item))
                        duplicates.Add(item);
                }
            }
            Console.WriteLine("Found {0} duplicates", duplicates.Count());
        }

    }
}
