using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class StepInstruction
    {
        public StepInstruction()
        {
            finished = false;
            dependencies = new List<char>();
            finishTime = 0;
        }

        public List<char> dependencies;

        public char name { get; set; }
        public bool finished { get; set; }
        public int finishTime { get; set; }

        internal void AddDependency(char dep)
        {
            dependencies.Add(dep);
            dependencies.Sort();
        }

        public void Print()
        {
            if (dependencies.Count == 0)
            {
                Console.WriteLine(name + " can finish");
            }
            else
            {
                Console.Write(name + " must wait for ");
                foreach (var item in dependencies)
                {
                    Console.Write("{0} ", item);
                }
                Console.WriteLine("to finish before proceding");
            }
        }

        public bool CanDoStep(ref Dictionary<char, StepInstruction> steps)
        {
            if (dependencies.Count == 0)
                return true;

            bool depsFinished = true;
            foreach (var item in dependencies)
            {
                if (steps.ContainsKey(item))
                {
                    if (steps[item].finished == false)
                        depsFinished = false;
                }
            }
            return depsFinished;
        }

        
        public void DoStep(int currentTime)
        {
            if( currentTime >= finishTime)
                finished = true;
        }

        internal bool InProgress()
        {
            return (finishTime > 0);
        }

        internal void StartWork(int currentSecond, ref Dictionary<char, int> secondsToFinish)
        {
            finishTime = currentSecond + secondsToFinish[name] -1;
        }
    }
}
