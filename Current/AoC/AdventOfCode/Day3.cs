using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class Day3
    {
        public Day3()
        {

        }

        public void Run()
        {
            /*
            #1 @ 1,3: 4x4
            #2 @ 3,1: 4x4
            #3 @ 5,5: 2x2 
            */

            int matrixwidth = 1000;
            int matrixheight = 1000;
            int[,] matrix = new int[matrixwidth, matrixheight];

            Dictionary<int, Data> input = new Dictionary<int, Data>();
            char[] delimiterChars = { '@', ':', ',', 'x' };
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day3.txt");

            foreach (string line in lines)
            {
                string[] d = line.Split(delimiterChars);
                //Console.WriteLine("Line {0} has {1} pieces", line, d.Length);
                Data s = new Data();
                s.id = Int32.Parse(d[0].Trim('#'));
                s.fromleft = Int32.Parse(d[1].Trim(' '));
                s.fromtop = Int32.Parse(d[2].Trim(' '));
                s.width = Int32.Parse(d[3].Trim(' '));
                s.height = Int32.Parse(d[4].Trim(' '));
                input[s.id] = s;
            }

            foreach (var item in input)
            {
                int xpos = item.Value.fromleft;
                int ypos = item.Value.fromtop;
                for (int i = 0; i < item.Value.width; i++)
                {
                    for (int j = 0; j < item.Value.height; j++)
                    {
                        matrix[i + xpos, j + ypos]++;
                    }
                }
            }

            int overlaps = 0;
            for (int i = 0; i < matrixheight; i++)
            {
                for (int j = 0; j < matrixwidth; j++)
                {
                    //if (matrix[j, i] == 0)
                    //    Console.Write('.');
                    //else
                    //    Console.Write(matrix[j, i]);
                    if (matrix[j, i] > 1)
                        overlaps++;
                }
            }
            Console.WriteLine("Overlaps = {0}", overlaps);

            int overlapid = -1;
            foreach (var item in input)
            {
                bool boverlaps = false;
                int xpos = item.Value.fromleft;
                int ypos = item.Value.fromtop;
                for (int i = 0; i < item.Value.width; i++)
                {
                    for (int j = 0; j < item.Value.height; j++)
                    {
                        if (matrix[i + xpos, j + ypos] != 1)
                        {
                            boverlaps = true;
                            break;
                        }
                    }
                    if (boverlaps)
                        break;
                }
                if (boverlaps)
                    continue;
                overlapid = item.Value.id;
            }
            Console.WriteLine("Id with no overlaps {0}", overlapid);
        }
    }
}
