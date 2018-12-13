using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace AdventOfCode
{
    public class Plant
    {
        public int index { get; set; }
        public char state { get; set; }
    }
    class Day12
    {
        public Day12()
        {
            rules = new Dictionary<string, char>();
            cstates = new List<Plant>();
        }

        public void Run()
        {
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day12.txt");

            foreach (var line in lines)
            {
                if (line.Length == 0)
                    continue;
                if (line.StartsWith("initial state:"))
                {
                    var initialState = line.TrimStart("initial state: ".ToArray());
                    var idx = 0;
                    foreach (var c in initialState)
                    {
                        cstates.Add(new Plant() { index = idx, state = c });
                        idx++;
                    }
                }
                else
                {
                    var l = line.Split(' ');
                    rules[l[0]] = l[2].ToCharArray()[0];
                    var rule = Regex.Match(line, @"[.#]*(\s)?(=)?(>)?(\s)?[.#]*");
                    //rules[rule[0]] = rule[1];

                }
            }

            PrintStates();
            //PrintRules();

            for (int i = 0; i < 50000000000; i++)
            {
                DoGeneration();
                //PrintStates();
                if (i % 1000 == 0)
                    Console.WriteLine(i);
            }

            Console.WriteLine("Sum of indices where pots have plants is {0}", PlantCount());
        }

        private int PlantCount()
        {
            int count = 0;
            foreach (var plant in cstates)
            {
                if (plant.state == '#')
                    count+= plant.index;
            }
            return count;
        }
        private void DoGeneration()
        {
            // Add 2 pots to the left and right if the first/last two are not empty

            while (!(cstates[0].state == '.' && cstates[1].state == '.' && cstates[2].state == '.'))
            {
                cstates.Insert(0, new Plant() { index = cstates[0].index - 1, state = '.' });
            }

            
            while (!(cstates[cstates.Count-1].state == '.' && cstates[cstates.Count - 2].state == '.' && cstates[cstates.Count - 3].state == '.'))
            {
                cstates.Add(new Plant() { index = cstates[cstates.Count - 1].index + 1, state = '.' });
            }

            List<Plant> newgen = new List<Plant>();

            for (int i = 2; i < cstates.Count - 2; i++)
            {
                var range = cstates.GetRange(i - 2, 5);
                string key = string.Empty;
                foreach (var c in range)
                {
                    key += c.state;
                }

                if (rules.ContainsKey(key))
                {
                    newgen.Add(new Plant() { index = cstates[i].index, state = rules[key] });
                }
                else
                    newgen.Add(cstates[i]);
            }
            cstates = newgen;
            currentGen++;
        }

        private void PrintStates()
        {
            //foreach (var c in states)
            //{
            //    Console.Write(c.Value);
            //}

            //Console.WriteLine("\n");
            Console.Write("{0} ", currentGen);
            int numplants = 0;
            foreach (var c in cstates)
            {
                if (c.state == '#')
                    numplants++;
                Console.Write(c.state);
            }
            Console.WriteLine(" {0}", numplants);
        }

        private void PrintRules()
        {
            foreach (var rule in rules)
            {
                Console.WriteLine("{0} maps to {1}", rule.Key, rule.Value);
            }
        }

        List<Plant> cstates;
        Dictionary<string, char> rules;
        int currentGen = 0;
        int currentCenterIndex = 0;
    }
}
