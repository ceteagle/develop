using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class Day6
    {
        public Day6()
        {

        }

        public void Run()
        {
            char[] delimiterChars = { ',' };
            int currId = 0;

            string[] lines = System.IO.File.ReadAllLines(@"..\..\day6.txt");
            List<CoordInfo> coords = new List<CoordInfo>();
            foreach (var line in lines)
            {
                string[] d = line.Split(delimiterChars);
                coords.Add(new CoordInfo() { id = currId++, x = Int32.Parse(d[0]), y = Int32.Parse(d[1]) });
            }

            foreach (var coord in coords)
            {
                Console.WriteLine("{0}: {1},{2}", coord.id, coord.x, coord.y);
            }

            int minx = int.MaxValue;
            int maxx = int.MinValue;

            int miny = int.MaxValue;
            int maxy = int.MinValue;

            foreach (var coord in coords)
            {
                if (coord.x < minx)
                    minx = coord.x;
                if (coord.x > maxx)
                    maxx = coord.x;

                if (coord.y < miny)
                    miny = coord.y;
                if (coord.y > maxy)
                    maxy = coord.y;
            }

            Console.WriteLine("Max x {0} Min x {1}  Max y {2} Min y {3}", maxx, minx, maxy, miny);

            Grid[,] grid = new Grid[maxx + 1, maxy + 1];
            for (int y = miny; y < maxy; y++)
            {
                for (int x = minx; x < maxx; x++)
                {
                    grid[x, y] = new Grid() { closestCoord = -1, distance = int.MaxValue };
                }
            }


            for (int y = miny; y < maxy; y++)
            {
                for (int x = minx; x < maxx; x++)
                {
                    // Find closest input coord
                    foreach (var coord in coords)
                    {
                        if (coord.x == x && coord.y == y)
                        {
                            grid[x, y].distance = 0;
                            grid[x, y].closestCoord = coord.id;
                            break;
                        }
                        int distance = Helper.ManhattanDistance(coord.x, x, coord.y, y);
                        if (distance < grid[x, y].distance)
                        {
                            // Closer
                            grid[x, y].distance = distance;
                            grid[x, y].closestCoord = coord.id;
                        }
                        else if (distance == grid[x, y].distance)
                        {
                            grid[x, y].closestCoord = -999;
                        }
                    }
                }
            }
            bool printGrid = false;
            if (printGrid)
            {
                for (int y = miny; y < maxy; y++)
                {
                    for (int x = minx; x < maxx; x++)
                    {
                        Console.Write("{0} ", grid[x, y].closestCoord == -999 ? '.' : grid[x, y].closestCoord);
                    }
                    Console.WriteLine();
                }
            }

            // Loop over grid data finding what id has most points
            Dictionary<int, int> gridStatus = new Dictionary<int, int>();
            foreach (var coord in coords)
            {
                gridStatus[coord.id] = 0;
            }
            for (int y = miny; y < maxy; y++)
            {
                for (int x = minx; x < maxx; x++)
                {
                    if (grid[x, y].closestCoord == -999)
                        continue;
                    gridStatus[grid[x, y].closestCoord]++;
                }
            }

            int idWithMaxPoints = -1;
            int maxNumPoints = 0;
            foreach (var item in gridStatus)
            {
                if (item.Value > maxNumPoints)
                {
                    maxNumPoints = item.Value;
                    idWithMaxPoints = item.Key;
                }
            }

            foreach (var coord in coords)
            {
                if (coord.id != idWithMaxPoints)
                    continue;
                Console.WriteLine("Coord with most is {0} with {1} points ({2},{3})", idWithMaxPoints, maxNumPoints, coord.x, coord.y);
            }

            // Part 2

            foreach (var coord in coords)
            {
                if (coord.x < minx)
                    minx = coord.x;
                if (coord.x > maxx)
                    maxx = coord.x;

                if (coord.y < miny)
                    miny = coord.y;
                if (coord.y > maxy)
                    maxy = coord.y;
            }


            int maxDistance = 10000;

            List<Coord> possiblePoints = new List<Coord>();

            for (int y = miny; y < maxy; y++)
            {
                for (int x = minx; x < maxx; x++)
                {
                    List<CoordInfo> l = new List<CoordInfo>();

                    // Find closest input coord
                    int totalDistance = 0;
                    foreach (var coord in coords)
                    {
                        totalDistance += Helper.ManhattanDistance(coord.x, x, coord.y, y);
                    }

                    if (totalDistance < maxDistance)
                    {
                        Coord ccc = new Coord();
                        ccc.x = x;
                        ccc.y = y;
                        possiblePoints.Add(ccc);
                    }
                }
            }

            Console.WriteLine("possible points size {0}", possiblePoints.Count);


        }
    }
}
