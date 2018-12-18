using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace AdventOfCode
{

    class Water : Coord
    {
        public Water(char display = '~')
        {
            Moving = true;
            c = display;
            Filling = false;
            Prev = null;
        }

        private char c { get; set; }
        public char Display
        {
            get
            {
                return (Moving ? '|' : c);
            }
        }

        public Water Prev { get; set; }
        public bool Moving { get; set; }
        public bool Filling { get; set; }
    }
    class Day17
    {
        List<Coord> clay;
        int xmin;
        int xmax;
        int ymin;
        int ymax;
        Water waterSource;
        List<Water> water;
        List<Water> runningWater;
        char[,] ground;
        public bool WaterRunning { get; set; }

        public Day17()
        {
            clay = new List<Coord>();
            runningWater = new List<Water>();

            xmin = ymin = Int32.MaxValue;
            xmax = ymax = Int32.MinValue;

            water = new List<Water>();
            waterSource = new Water('+') { x = 500, y = 0, Filling = true };
            water.Add(waterSource);
            runningWater.Add(waterSource);
            WaterRunning = true;
        }


        public void Part1()
        {
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

            InitGround();

            //Draw();

            while (WaterRunning)
            {
                UpdateWater();
                //Draw();
                //Console.ReadKey();
            }

            //Draw();
            Console.WriteLine("Number of water cells = {0}", water.Count() - 1);
            WriteToFile();
        }

        private void InitGround()
        {
            ground = new char[xmax + 1, ymax + 1];
            for (int y = 0; y <= ymax; y++)
            {
                for (int x = xmin; x <= xmax; x++)
                {
                    ground[x, y] = '.';
                }
            }

            foreach (var item in clay)
            {
                ground[item.x, item.y] = '#';
            }
        }

        private void UpdateWater()
        {
            var newRunningWater = new List<Water>();

            foreach (var last in runningWater)
            {
                if (last.y >= ymax || last.x >= xmax || last.Moving == false)
                    continue;
                char nextLevel = ground[last.x, last.y + 1];

                if (nextLevel == '.')
                {
                    if (last.y + 1 <= ymax)
                    {
                        last.Filling = false;
                        var w = new Water() { x = last.x, y = last.y + 1, Filling = true };
                        w.Prev = last;
                        water.Add(w);
                        newRunningWater.Add(w);
                    }
                }
                else if (nextLevel == '#' || nextLevel == '~')
                {
                    // If left and right are clay or non moving water then stop moving
                    if ((ground[last.x - 1, last.y] == '#' || ground[last.x - 1, last.y] == '~') && (ground[last.x + 1, last.y] == '#' || ground[last.x + 1, last.y] == '~'))
                    {
                        last.Moving = false;
                        last.Filling = false;
                        ground[last.x, last.y] = last.Display;
                        //if (ground[last.x - 1, last.y - 1] != '#' && ground[last.x + 1, last.y - 1] != '#')
                        //{
                        //}

                        //var allmoving = water.FindAll(u => u.Moving);
                        //allmoving.OrderBy(u => u.y);
                        //allmoving.Reverse();
                        //foreach (var item in allmoving)
                        //{
                        //    if (runningWater.Contains(item))
                        //        continue;

                        //    newRunningWater.Add(item);
                        //    break;
                        //}
                        var row = runningWater.FindAll(u => u.y == last.y);
                        if (row.Count() == 1)
                        {
                            var w = last.Prev;
                            while (w != null && !w.Moving)
                            {
                                w = w.Prev;
                                if( w.y < (last.y-1))
                                {
                                    w = null;
                                    break;
                                }
                            }
                            if (w != null)
                                newRunningWater.Add(w);
                        }

                        if(row.Count() > 1)
                        {
                            if( row.FindAll(u => u.Moving).Count() == 0)
                            {
                                var w = last.Prev;
                                while (w != null && !w.Moving)
                                {
                                    w = w.Prev;
                                    if (w.y < (last.y - 1))
                                    {
                                        w = null;
                                        break;
                                    }
                                }
                                if (w != null)
                                    newRunningWater.Add(w);
                            }
                        }
                     }
                    else
                    {
                        // Fill left and right of current location
                        //
                        if (ground[last.x - 1, last.y] == '.')
                        {
                            last.Moving = false;
                            ground[last.x, last.y] = last.Display;
                            var w = new Water() { x = last.x - 1, y = last.y };
                            w.Prev = last;
                            water.Add(w);
                            newRunningWater.Add(w);
                        }
                        if (ground[last.x + 1, last.y] == '.')
                        {
                            last.Moving = false;
                            ground[last.x, last.y] = last.Display;

                            var w = new Water() { x = last.x + 1, y = last.y };
                            w.Prev = last;
                            water.Add(w);
                            newRunningWater.Add(w);
                        }
                    }
                }
            }
            if (newRunningWater.Count() == 0)
                WaterRunning = false;
            runningWater = newRunningWater;
        }

        private void WriteToFile()
        {
            char[,] display = new char[xmax + 1, ymax + 1];
            for (int y = 0; y <= ymax; y++)
            {
                for (int x = xmin; x <= xmax; x++)
                {
                    display[x, y] = ground[x, y];
                }
            }

            display[waterSource.x, waterSource.y] = '+';

            // Overlay water
            //
            foreach (var w in water)
            {
                display[w.x, w.y] = w.Display;
            }

            string output = string.Empty;

            using (System.IO.StreamWriter file =
            new System.IO.StreamWriter(@"day17output.xls"))
            {
                for (int y = 0; y <= ymax; y++)
                {
                    output = string.Empty;
                    for (int x = xmin; x <= xmax; x++)
                    {
                        output += display[x, y];
                        output += '\t';
                    }
                    if (y == ymin)
                        output += "<== YMIN";
                    if (y == ymax)
                        output += "  <<== YMAX";
                    file.WriteLine(output);
                }
            }
        }

        public void Draw()
        {
            Console.Clear();

            char[,] display = new char[xmax + 1, ymax + 1];
            for (int y = 0; y <= ymax; y++)
            {
                for (int x = xmin; x <= xmax; x++)
                {
                    display[x, y] = ground[x, y];
                }
            }

            display[waterSource.x, waterSource.y] = '+';

            // Overlay water
            //
            foreach (var w in water)
            {
                display[w.x, w.y] = w.Display;
            }

            // Draw
            //
            for (int y = 0; y <= ymax; y++)
            {
                for (int x = xmin; x <= xmax; x++)
                {
                    Console.Write(display[x, y]);
                }
                if (y == ymin)
                    Console.Write("  <<== YMIN");
                if (y == ymax)
                    Console.Write("  <<== YMAX");
                Console.WriteLine();
            }
        }
    }
}
