using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class Day2
    {
        public Day2()
        {

        }

        public void Run()
        {
            int twiceCount = 0;
            int thriceCount = 0;
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day2.txt");
            foreach (string line in lines)
            {
                Dictionary<char, int> counts = new Dictionary<char, int>();
                foreach (char c in line)
                {
                    if (counts.ContainsKey(c))
                        continue;
                    int count = line.Count(f => f == c);
                    counts.Add(c, count);
                }

                if (counts.ContainsValue(2))
                    twiceCount++;
                if (counts.ContainsValue(3))
                    thriceCount++;
                counts.Clear();
                // Use a tab to indent each line of the file.
                //Console.WriteLine("\t" + line);
            }

            Console.WriteLine("Checksum = {0}", twiceCount * thriceCount);


            for (int i = 0; i < lines.Count(); i++)
            {

                var linelen = lines[i].Count();

                for (int j = i + 1; j < lines.Count(); j++)
                {
                    int nummissed = 0;
                    for (int k = 0; k < linelen; k++)
                    {
                        if (lines[i][k] != lines[j][k])
                            nummissed++;
                        if (nummissed == 3)
                            break;
                        if (k == linelen - 1)
                        {
                            Console.WriteLine("Found match {0} {1}", lines[i], lines[j]);
                        }

                    }
                }
            }
        }
    }
}
