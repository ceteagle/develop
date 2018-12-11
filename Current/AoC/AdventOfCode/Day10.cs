using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class Star
    {
        public Star()
        {
            x = y = vx = vy = 0;
        }

        public void UpdatePosition()
        {
            x += vx;
            y += vy;
        }

        public int x;
        public int y;
        public int vx;
        public int vy;

    }

    class Day10
    {
        public Day10()
        {
            stars = new List<Star>();
            second = 0;
        }
        List<Star> stars;
        public int maxwidth;
        public int maxheight;
        public int second;
        public void Run()
        {
            
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day10.txt");
            foreach (var line in lines)
            {
                Star s = new Star();
                var ss = line.Split(new char[] { '<', ',', '>' });
                s.x = Int32.Parse(ss[1]);
                s.y = Int32.Parse(ss[2]);
                s.vx = Int32.Parse(ss[4]);
                s.vy = Int32.Parse(ss[5]);

                stars.Add(s);
            }

            while (true)
            {
                if (Draw())
                    Console.ReadKey();
                Update();
                second++;
            }

        }

        public void Update()
        {
            foreach (var star in stars)
            {
                star.UpdatePosition();
            }
        }

        public int Width()
        {
            int min = Int32.MaxValue;
            int max = Int32.MinValue;
            foreach (var star in stars)
            {
                if (star.x > max)
                    max = star.x;
                if (star.x < min)
                    min = star.x;
            }

            return max-min;
        }

        public int Height()
        {
            int min = Int32.MaxValue;
            int max = Int32.MinValue;
            foreach (var star in stars)
            {
                if (star.y > max)
                    max = star.x;
                if (star.y < min)
                    min = star.x;
            }

            return max - min;
        }

        public bool Draw()
        {
            int dw = Width();
            int dh = Height();

            Console.Clear();
            Console.WriteLine("Current second is {0} {1} {2}", second, dw, dh);

            if (dw > 100 || dh > 100)
                return false;

            int width = 200;
            int height = 300;
            char[,] display = new char[width+1, height+1];

            foreach (var star in stars)
            {
                if (star.x < 0 || star.x > width)
                {
                    continue;
                }
                if (star.y < 0 || star.y > height)
                {
                    continue;
                }
                display[star.x, star.y] = 'X';
            }

            
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    Console.Write(display[x, y]);
                }
                Console.WriteLine();
            }
            return true;
        }

    }
}
