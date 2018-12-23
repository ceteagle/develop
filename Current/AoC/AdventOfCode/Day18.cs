using System;
using System.Collections.Generic;
using System.Linq;

namespace AdventOfCode
{
    /*
    An open acre will become filled with trees if three or more adjacent acres contained trees. Otherwise, nothing happens.
    An acre filled with trees will become a lumberyard if three or more adjacent acres were lumberyards. Otherwise, nothing happens.
    An acre containing a lumberyard will remain a lumberyard if it was adjacent to at least one other lumberyard and at least one acre containing trees.
    Otherwise, it becomes open.
    */
    class Day18
    {
        char[,] grid;

        const char ground = '.';
        const char tree = '|';
        const char lumberyard = '#';
        public int Minutes { get; set; }
        //Dictionary<long, int> totals;
        List<int> totals;


        public Day18()
        {
            grid = new char[50, 50];
            Minutes = 0;
            totals = new List<int>();
        }

        public void Part1()
        {
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day18.txt");
            //string[] lines = System.IO.File.ReadAllLines(@"..\..\d18test.txt");
            Read(lines);

            int treecount = 0;
            int groundcount = 0;
            int lumberyardcount = 0;

            //while (Minute < 10) // Part 1
            while (Minutes < 1000000000)  // Part2
            {
                char[,] newgrid = new char[50, 50];
                for (int y = 0; y < 50; y++)
                {
                    for (int x = 0; x < 50; x++)
                    {
                        switch (grid[x, y])
                        {
                            case ground:
                                treecount = Count(x, y, tree);
                                if (treecount >= 3)
                                {
                                    newgrid[x, y] = tree;
                                }
                                else
                                {
                                    newgrid[x, y] = grid[x, y];
                                }

                                break;
                            case tree:
                                lumberyardcount = Count(x, y, lumberyard);
                                if (lumberyardcount >= 3)
                                {
                                    newgrid[x, y] = lumberyard;
                                }
                                else
                                {
                                    newgrid[x, y] = grid[x, y];
                                }

                                break;

                            case lumberyard:
                                lumberyardcount = Count(x, y, lumberyard);
                                treecount = Count(x, y, tree);
                                if (lumberyardcount > 0 && treecount > 0)
                                {
                                    newgrid[x, y] = lumberyard;
                                }
                                else
                                {
                                    newgrid[x, y] = ground;
                                }

                                break;
                        }
                    }

                }
                grid = newgrid;

                //Draw();
                CalculatePart1();

                CheckForPattern();

                //Console.ReadKey();
                if ((Minutes % 10000) == 0)
                {
                    Console.WriteLine("{0} Minutes", Minutes);
                }

                Minutes++;
            }

            CalculatePart1();
        }

        private void CalculatePart1()
        {
            int totalwooded = 0;
            int totallumberyards = 0;
            for (int y = 0; y < 50; y++)
            {
                for (int x = 0; x < 50; x++)
                {
                    if (grid[x, y] == lumberyard)
                    {
                        totallumberyards++;
                    }

                    if (grid[x, y] == tree)
                    {
                        totalwooded++;
                    }
                }
            }
            totals.Add(totalwooded * totallumberyards);
            //Console.WriteLine("Part1 {0} * {1} = {2}", totalwooded, totallumberyards, totalwooded * totallumberyards);
        }

        private bool FindMatches(int start1, int start2, ref int nummatches)
        {
            if (totals[start1] != totals[start2])
            {
                return false;
            }

            bool matches = true;
            int matchcount = 1;

            int current1 = start1 + 1;
            int current2 = start2 + 1;

            while (matches)
            {
                if (current2 >= totals.Count || current1 >= start2)
                {
                    break;
                }
                if (totals[current1] != totals[current2])
                {
                    matches = false;
                    break;
                }
                if (nummatches != 0)
                {
                    if ((start1 + matchcount) == nummatches)
                    {
                        break;
                    }
                }
                current1++;
                current2++;
                matchcount++;
            }
            if (nummatches == 0)
            {
                nummatches = matchcount;
            }

            return matches;
        }
        private void CheckForPattern()
        {
            int count = totals.Count();
            if (count < 100)
            {
                return;
            }

            Console.Clear();
            int startIdx1 = 0;
            int startIdx2 = 0;
            int maxPatternSize = 0;
            int start1atmax = 0;
            int start2atmax = 0;
            int maxrepeats = 0;
            for (int i = 0; i < count; i++)
            {
                startIdx1 = i;
                for (int j = i + 1; j < count; j++)
                {
                    startIdx2 = j;
                    int nummatches = 0;
                    if (FindMatches(startIdx1, startIdx2, ref nummatches) && nummatches > 1)
                    {

                        {
                            bool nonrepeating = false;
                            int numrepeats = 0;

                            for (int l = startIdx2; l < count; l += nummatches)
                            {
                                nummatches = nummatches;
                                if (FindMatches(startIdx1, l, ref nummatches))
                                {
                                    if (nummatches != nummatches)
                                    {
                                        //Console.WriteLine("Non repeating match");
                                        nonrepeating = true;
                                        break;
                                    }
                                    numrepeats++;
                                }
                            }

                            if (numrepeats > maxrepeats)
                            {
                                maxrepeats = numrepeats;
                                start1atmax = startIdx1;
                                start2atmax = startIdx2;
                                maxPatternSize = nummatches;
                            }
                            //if (nonrepeating == false && numrepeats > 2)
                            //    Console.WriteLine("REPEATING PATTERN : starting at {0} and {1} with {2} matches repeats {3} times", startIdx1, startIdx2, nummatches, numrepeats);
                        }
                        //Console.WriteLine("Found pattern starting at {0} and {1} with {2} matches", startIdx1, startIdx2, nummatches);
                    }
                }

            }
            if (maxrepeats > 10)
            {
                Minutes = 1000000000;
                Console.WriteLine("REPEATING PATTERN : starting at {0} and {1} with {2} matches repeats {3} times", start1atmax, start2atmax, maxPatternSize, maxrepeats);
                Console.WriteLine("Part2 = {0}", totals[start1atmax + (Minutes - start1atmax) % maxPatternSize - 1]);
            }

        }
        private void Read(string[] lines)
        {
            int x = 0;
            int y = 0;
            foreach (var line in lines)
            {
                x = 0;
                foreach (char c in line)
                {
                    grid[x++, y] = c;
                }
                y++;
            }
        }

        public void Part2()
        {

        }

        private int Count(int x, int y, char key)
        {
            int count = 0;

            if ((x - 1) >= 0 && (y - 1) >= 0 && grid[x - 1, y - 1] == key)
            {
                count++;
            }

            if ((y - 1) >= 0 && grid[x, y - 1] == key)
            {
                count++;
            }

            if ((x + 1) < 50 && (y - 1) >= 0 && grid[x + 1, y - 1] == key)
            {
                count++;
            }

            if ((x - 1) >= 0 && grid[x - 1, y] == key)
            {
                count++;
            }

            if ((x + 1) < 50 && grid[x + 1, y] == key)
            {
                count++;
            }

            if ((x - 1) >= 0 && (y + 1) < 50 && grid[x - 1, y + 1] == key)
            {
                count++;
            }

            if ((y + 1) < 50 && grid[x, y + 1] == key)
            {
                count++;
            }

            if ((x + 1) < 50 && (y + 1) < 50 && grid[x + 1, y + 1] == key)
            {
                count++;
            }

            return count;
        }

        private void Draw()
        {
            Console.Clear();

            for (int y = 0; y < 50; y++)
            {
                for (int x = 0; x < 50; x++)
                {
                    Console.Write(grid[x, y]);
                }
                Console.WriteLine();
            }
        }
    }
}
