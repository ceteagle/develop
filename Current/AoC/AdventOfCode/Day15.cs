using AdventOfCode.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    public enum UnitType
    {
        Elf,
        Goblin
    }

    class Unit : Cell
    {
        public Unit(UnitType type)
        {
            Type = type;
            HitPoints = 200;
            Targeting = null;
        }

        public char Char
        {
            get
            {
                return (Type == UnitType.Elf ? 'E' : 'G');
            }

        }
        public UnitType Type { get; private set; }
        public bool IsAlive
        {
            get
            {
                return HitPoints > 0;
            }
        }
        public int HitPoints { get; set; }
        public Unit Targeting { get; set; }
    }
    class Day15
    {
        public Day15()
        {
            units = new List<Unit>();
            round = 0;
        }
        public int width { get; set; }
        public int height { get; set; }

        public void Run()
        {
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day15.txt");
            //string[] lines = System.IO.File.ReadAllLines(@"..\..\d15sample.txt");
            width = lines[0].Length;
            height = lines.Length;

            map = new char[lines[0].Length, lines.Length];
            int x = 0;
            int y = 0;
            foreach (var line in lines)
            {
                foreach (char c in line)
                {
                    if (c == 'G')
                    {
                        map[x, y] = '.';
                        units.Add(new Unit(UnitType.Goblin) { X = x, Y = y });
                    }
                    else if (c == 'E')
                    {
                        map[x, y] = '.';
                        units.Add(new Unit(UnitType.Elf) { X = x, Y = y });
                    }
                    else
                        map[x, y] = c;
                    x++;
                }
                x = 0;
                y++;
            }

            while (!Victory())
            {
                PrintMap();
                DoRound();
                //System.Threading.Thread.Sleep(10);
                //Console.ReadKey();
            }

            int hpsum = 0;
            PrintMap();
            foreach (var unit in units)
            {
                if (!unit.IsAlive)
                    continue;
                hpsum += unit.HitPoints;
            }
            Console.WriteLine("Part 1 Answer = {0}", round * hpsum);
        }

        private List<Unit> FindTargets(Unit unit)
        {
            List<Unit> targets = new List<Unit>();
            foreach (var u in units)
            {
                if (u.Type == unit.Type)
                    continue;
                if (!u.IsAlive)
                    continue;
                targets.Add(u);
            }
            return targets.OrderBy(u => u.Y).ThenBy(u => u.X).ToList();
        }

        private bool Victory()
        {
            int elfCount = 0;
            int goblinCount = 0;
            foreach (var unit in units)
            {
                if (!unit.IsAlive)
                    continue;
                if (unit.Type == UnitType.Elf)
                    elfCount++;
                else if (unit.Type == UnitType.Goblin)
                    goblinCount++;
                if (elfCount > 0 && goblinCount > 0)
                    break;
            }
            return (elfCount == 0 || goblinCount == 0);
        }

        private void DoRound()
        {
            var o = units.OrderBy(u => u.Y).ThenBy(u => u.X);

            foreach (var unit in o)
            {
                if (!unit.IsAlive)
                    continue;

                var cmap = GetMapWithUnits();
                var targets = FindTargets(unit);
                BFS bfs = new BFS(cmap, unit.X, unit.Y, width, height);
                List<Unit> closestUnits = new List<Unit>();

                int closest = Int32.MaxValue;
                foreach (var target in targets)
                {
                    bfs.Reset();
                    bfs.ec = target.X;
                    bfs.er = target.Y;

                    int distance = bfs.Solve();
                    if (distance > 0 && distance <= closest)
                    {
                        if (distance == closest)
                        {
                            closestUnits.Add(target);
                        }
                        else
                        {
                            closestUnits.Clear();
                            closestUnits.Add(target);
                        }
                        closest = distance;
                    }
                }

                //Console.WriteLine("Unit {0} @ {1},{2} has {3} targets", unit.Char, unit.X, unit.Y, targets.Count);
                //foreach (var target in closestUnits)
                //{
                //    Console.WriteLine("{0},{1} target @ {2},{3} {4} units away", unit.X, unit.Y, target.X, target.Y, closest);
                //    var path = bfs.Path();
                //    foreach (var item in path)
                //    {
                //        Console.WriteLine("{0},{1}", item.X, item.Y);
                //    }
                //}

                if (closestUnits.Count > 0)
                {
                    if (closest == 1)
                    {
                        var a = closestUnits.OrderBy(u => u.HitPoints).ThenBy(u => u.Y).ThenBy(u => u.X).ToList();
                        a[0].HitPoints -= 3;
                        unit.Targeting = a[0];
                    }
                    else
                    {
                        var a = closestUnits.OrderBy(u => u.Y).ThenBy(u => u.X).ToList();
                        unit.Targeting = a[0];

                        var path = bfs.Path(a[0].X, a[0].Y);
                        if (path.Count > 1)
                        {
                            unit.X = path[1].X;
                            unit.Y = path[1].Y;
                        }
                        if (closest == 2)
                        {
                            unit.Targeting.HitPoints -= 3;
                        }
                    }
                }
                if (Victory())
                    return;
            }
            round++;
        }

        private char[,] GetMapWithUnits()
        {
            char[,] cmap = new char[width, height];
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    cmap[x, y] = map[x, y];
                }
            }
            foreach (var unit in units)
            {
                if (!unit.IsAlive)
                    continue;
                cmap[unit.X, unit.Y] = unit.Char;
            }
            return cmap;
        }
        private void PrintMap()
        {
            Console.Clear();

            var cmap = GetMapWithUnits();

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    switch (cmap[x, y])
                    {
                        case 'G':
                            Console.ForegroundColor = ConsoleColor.Blue;
                            break;
                        case 'E':
                            Console.ForegroundColor = ConsoleColor.Green;
                            break;
                        case '#':
                        case '.':
                            Console.ResetColor();
                            break;

                        default:
                            break;
                    }
                    Console.Write(cmap[x, y]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();

            Console.WriteLine("After {0} rounds", round);
            int row = -1;
            foreach (var unit in units.OrderBy(u => u.Y).ThenBy(u => u.X).ToList())
            {
                if (row == -1)
                    row = unit.Y;

                if (unit.Y > row)
                {
                    Console.WriteLine();
                    row = unit.Y;
                }
                Console.Write("{0}({1}) ", unit.Char, unit.HitPoints);
                if(unit.Targeting != null)
                {
                    Console.Write("T({0},{1}) ", unit.Targeting.X, unit.Targeting.Y);
                }


            }
        }

        int round;

        char[,] map;
        List<Unit> units;

    }

}
