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
        public int LoopCounter { get; set; }
        public Day17()
        {
            clay = new List<Coord>();
            runningWater = new List<Water>();
            LoopCounter = 0;
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

            xmax++;
            ymax++;

            InitGround();

            //Draw();

            while (WaterRunning)
            {
                UpdateWater();
                //Draw();
                if (runningWater.Count() > 2)
                {
                    //Draw();
                    //Console.ReadKey();
                }
                LoopCounter++;
            }

            //Draw();
            Console.WriteLine("Number of water cells = {0} ==> Loop Counter = {1}", water.Count() - 1, LoopCounter);
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
            Dictionary<int, bool> added = new Dictionary<int, bool>();

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
                    if(nextLevel == '~')
                    {
                        // Check to see if this has already been filled by another stream
                        //

                        int xval = last.x;
                        int yplus1 = last.y + 1;
                        // Find #
                        //
                        while (ground[xval, yplus1] != '.')
                        {
                            xval++;
                        }
                        if (water.Find(u => u.x == xval && u.y == yplus1) != null && ground[xval-1,last.y] == '.')
                            continue;
                        xval = last.x;
                        while (ground[xval, yplus1] != '.')
                        {
                            xval--;
                        }
                        if (water.Find(u => u.x == xval && u.y == yplus1) != null && ground[xval+1,last.y] == '.')
                            continue;
                        //    if(runningWater.FindAll(u => u.y > last.y).Count() > 0)
                        //    {
                        //        continue;
                        //    }
                    }
                    // Fill up row until dropoff
                    //

                    // Go Left
                    //
                    int left = last.x;
                    while (!(ground[left - 1, last.y] == '#' || ground[left - 1, last.y] == '~' || !(water.FindAll(u => u.x == left - 1 && u.y == last.y && u.Moving).Count() == 0)))
                    {
                        if (ground[left - 1, last.y + 1] == '.')
                            break;
                        left--;
                    }

                    // Go Right
                    //
                    int right = last.x;
                    while (!(ground[right + 1, last.y] == '#' || ground[right + 1, last.y] == '~' || !(water.FindAll(u => u.x == right + 1 && u.y == last.y && u.Moving).Count() == 0)))
                    {
                        if (ground[right + 1, last.y + 1] == '.')
                            break;
                        right++;
                    }

                    //if (nextLevel == '~')
                    //{
                    //    if (ground[left, last.y + 1] == '#' && (ground[right, last.y + 1] != '#' && water.FindAll(u=>u.x == right && u.y == last.y+1 && u.Moving).Count() > 0))
                    //    {
                    //        if (water.FindAll(u => u.x == right + 1 && u.y == last.y + 1).Count() > 0)
                    //            continue;
                    //    }
                    //    else if ((ground[left, last.y + 1] != '#' && water.FindAll(u=>u.x == left && u.y == last.y+1 && u.Moving).Count() > 0) && ground[right, last.y + 1] == '#')
                    //    {
                    //        if (water.FindAll(u => u.x == left - 1 && u.y == last.y + 1).Count() > 0)
                    //            continue;
                    //    }
                    //}

                    for (int i = left; i < last.x; i++)
                    {
                        int x = i;
                        int y = last.y;
                        if (water.FindAll(u => u.x == x && u.y == y).Count() == 0)
                        {
                            var w = new Water() { x = i, y = last.y, Moving = false };
                            ground[w.x, w.y] = w.Display;
                            water.Add(w);
                        }
                    }
                    for (int i = last.x + 1; i <= right; i++)
                    {
                        int x = i;
                        int y = last.y;

                        if (water.FindAll(u => u.x == x && u.y == y).Count() == 0)
                        {
                            var w = new Water() { x = i, y = last.y, Moving = false };
                            ground[w.x, w.y] = w.Display;
                            water.Add(w);
                        }
                    }

                    last.Moving = false;
                    ground[last.x, last.y] = last.Display;

                    //if (runningWater.FindAll(u => u.y == last.y && u.x != last.x).Count() > 0)
                    //    continue;
                    if (ground[left - 1, last.y + 1] == '.')
                    {
                        int x = left - 1;
                        int y = last.y;
                        if (water.FindAll(u => u.x == x && u.y == y).Count() == 0)
                        {
                            var w = new Water() { x = x, y = last.y };
                            water.Add(w);
                            newRunningWater.Add(w);
                            added[last.y] = true;
                        }
                    }

                    if (ground[right + 1, last.y + 1] == '.')
                    {
                        int x = right + 1;
                        int y = last.y;
                        if (water.FindAll(u => u.x == x && u.y == y).Count() == 0)
                        {
                            var w = new Water() { x = x, y = y };
                            water.Add(w);
                            newRunningWater.Add(w);
                            added[last.y] = true;
                        }
                    }

                    bool b = false;
                    if (added.ContainsKey(last.y))
                        b = added[last.y];
                    if (!b)
                    {
                        var prev = water.Find(u => u.x == last.x && u.y == last.y - 1);
                        if (prev == null)
                        {
                            // Find #
                            //
                            while (ground[right, last.y] != '#' && ground[right, last.y] != '~')
                            {
                                right++;
                            }
                            while (ground[left, last.y] != '#' && ground[left, last.y] != '~')
                            {
                                left--;
                            }
                            if(last.x == right)
                            {
                                prev = water.Find(u => u.y == last.y - 1 && u.x > left && u.Moving);
                            }
                            else if (last.x == left)
                            {
                                prev = water.Find(u => u.y == last.y - 1 && u.x < right && u.Moving);
                            }
                            else
                            {
                                prev = water.Find(u => u.y == last.y - 1 && (u.x > left && u.x < right) && u.Moving);
                            }
                            
                            if (prev != null)
                            {
                                newRunningWater.Add(prev);
                                added[last.y] = true;
                            }
                        }
                        else
                            newRunningWater.Add(prev);
                    }
                    //// If left and right are clay or non moving water then stop moving
                    //if ((ground[last.x - 1, last.y] == '#' || ground[last.x - 1, last.y] == '~') && (ground[last.x + 1, last.y] == '#' || ground[last.x + 1, last.y] == '~'))
                    //{
                    //    last.Moving = false;
                    //    last.Filling = false;
                    //    ground[last.x, last.y] = last.Display;
                    //    //if (ground[last.x - 1, last.y - 1] != '#' && ground[last.x + 1, last.y - 1] != '#')
                    //    //{
                    //    //}

                    //    //var allmoving = water.FindAll(u => u.Moving);
                    //    //allmoving.OrderBy(u => u.y);
                    //    //allmoving.Reverse();
                    //    //foreach (var item in allmoving)
                    //    //{
                    //    //    if (runningWater.Contains(item))
                    //    //        continue;

                    //    //    newRunningWater.Add(item);
                    //    //    break;
                    //    //}
                    //    var row = runningWater.FindAll(u => u.y == last.y);
                    //    if (row.Count() == 1)
                    //    {
                    //        var w = last.Prev;
                    //        while (w != null && !w.Moving)
                    //        {
                    //            w = w.Prev;
                    //            if( w.y < (last.y-1))
                    //            {
                    //                w = null;
                    //                break;
                    //            }
                    //        }
                    //        if (w != null)
                    //            newRunningWater.Add(w);
                    //    }

                    //    if(row.Count() > 1)
                    //    {
                    //        if( row.FindAll(u => u.Moving).Count() == 0)
                    //        {
                    //            var w = last.Prev;
                    //            while (w != null && !w.Moving)
                    //            {
                    //                w = w.Prev;
                    //                if (w.y < (last.y - 1))
                    //                {
                    //                    w = null;
                    //                    break;
                    //                }
                    //            }
                    //            if (w != null)
                    //                newRunningWater.Add(w);
                    //        }
                    //    }
                    // }
                    //else
                    //{
                    //    // Fill left and right of current location
                    //    //
                    //    if (ground[last.x - 1, last.y] == '.')
                    //    {
                    //        last.Moving = false;
                    //        ground[last.x, last.y] = last.Display;
                    //        var w = new Water() { x = last.x - 1, y = last.y };
                    //        w.Prev = last;
                    //        water.Add(w);
                    //        newRunningWater.Add(w);
                    //    }
                    //    if (ground[last.x + 1, last.y] == '.')
                    //    {
                    //        last.Moving = false;
                    //        ground[last.x, last.y] = last.Display;

                    //        var w = new Water() { x = last.x + 1, y = last.y };
                    //        w.Prev = last;
                    //        water.Add(w);
                    //        newRunningWater.Add(w);
                    //    }
                    //}
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
            int sxmin = Int32.MaxValue;
            int sxmax = Int32.MinValue;
            int symin = Int32.MaxValue;
            int symax = Int32.MinValue;

            foreach (var item in runningWater)
            {
                if (item.x > sxmax)
                    sxmax = item.x;
                if (item.x < sxmin)
                    sxmin = item.x;

                if (item.y > symax)
                    symax = item.y;
                if (item.y < symin)
                    symin = item.y;
            }

            int buffer = 30;
            sxmin -= buffer;
            sxmax += buffer;
            symin -= buffer;
            symax += buffer;

            if (sxmin < xmin)
                sxmin = xmin;
            if (sxmax > xmax)
                sxmax = xmax;

            if (symin < ymin)
                symin = ymin;
            if (symax > ymax)
                symax = ymax;

            Console.Clear();

            char[,] display = new char[sxmax - sxmin + 1, symax - symin + 1];
            for (int y = symin; y <= symax; y++)
            {
                for (int x = sxmin; x <= sxmax; x++)
                {
                    display[x - sxmin, y - symin] = ground[x, y];
                }
            }

            //char[,] display = new char[xmax + 1, ymax + 1];
            //for (int y = 0; y <= ymax; y++)
            //{
            //    for (int x = xmin; x <= xmax; x++)
            //    {
            //        display[x, y] = ground[x, y];
            //    }
            //}

            //display[waterSource.x, waterSource.y] = '+';

            // Overlay water
            //
            foreach (var w in water)
            {
                if (w.x >= sxmin && w.x < sxmax && w.y >= symin && w.y < symax)
                    display[w.x - sxmin, w.y - symin] = w.Display;
            }

            // Draw
            //
            for (int y = 0; y <= symax - symin; y++)
            {
                for (int x = 0; x <= sxmax - sxmin; x++)
                {
                    Console.Write(display[x, y]);
                }
                if (y == 0) Console.Write("Loop {0} ", LoopCounter);

                if (y == ymin)
                    Console.Write("  <<== YMIN");
                if (y == ymax)
                    Console.Write("  <<== YMAX");
                Console.WriteLine();
            }
            //for (int y = 0; y <= ymax; y++)
            //{
            //    for (int x = xmin; x <= xmax; x++)
            //    {
            //        Console.Write(display[x, y]);
            //    }
            //    if (y == ymin)
            //        Console.Write("  <<== YMIN");
            //    if (y == ymax)
            //        Console.Write("  <<== YMAX");
            //    Console.WriteLine();
            //}
        }
    }
}
