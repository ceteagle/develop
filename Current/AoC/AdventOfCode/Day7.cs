using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{


    class Day7
    {
        public Day7()
        {
            steps = new Dictionary<char, StepInstruction>();
            secondsToFinish = new Dictionary<char, int>();
            char c = 'A';
            for (int i = 1; i <= 26; i++)
            {
                secondsToFinish[c] = 60 + i;
                c++;
            }
            //Step U must be finished before step Q can begin.

            string[] lines = System.IO.File.ReadAllLines(@"..\..\day7.txt");
            foreach (var line in lines)
            {
                char beforeChar = line[5];
                char afterChar = line[36];

                if (steps.ContainsKey(beforeChar) == false)
                {
                    steps[beforeChar] = new StepInstruction() { name = beforeChar };
                }

                if (steps.ContainsKey(afterChar) == false)
                {
                    steps[afterChar] = new StepInstruction() { name = afterChar };
                }

                steps[afterChar].AddDependency(beforeChar);

                Console.WriteLine("{0} before {1}", beforeChar, afterChar);
            }
        }

        Dictionary<char, StepInstruction> steps;
        Dictionary<char, int> secondsToFinish;

        internal bool CanExit()
        {
            foreach (var step in steps)
            {
                if (!step.Value.finished)
                    return false;
            }
            return true;
        }

        internal void Run()
        {
            string outstr = string.Empty;

            List<char> charFull = new List<char>();
            int currentSecond = 0;
            int numworkers = 0;
            List<char> activeSteps = new List<char>();
            while (CanExit() == false)
            {
                List<char> c = new List<char>();
                foreach (var step in steps)
                {
                    if (step.Value.finished)
                        continue;

                    if (step.Value.CanDoStep(ref steps))
                    {
                        c.Add(step.Value.name);
                    }
                }

                if (c.Count > 0)
                {
                    c.Sort();
                    if (numworkers < 6)
                    {
                        foreach (var item in c)
                        {
                            if (steps[item].InProgress())
                                continue;
                            if (numworkers == 6)
                                break;
                            steps[item].StartWork(currentSecond, ref secondsToFinish);
                            numworkers++;
                        }
                    }

                    for (int i = 0; i < numworkers; i++)
                    {
                        if (steps[c[i]].InProgress())
                            steps[c[i]].DoStep(currentSecond);

                        if (steps[c[i]].finished)
                        {
                            numworkers--;
                            charFull.Add(c[i]);
                        }
                    }
                }
                currentSecond++;
            }

           foreach (var item in charFull)
            {
                Console.Write("{0}", item);
            }
            Console.WriteLine();

            Console.WriteLine("Time {0}", currentSecond);
        }
    }
}
