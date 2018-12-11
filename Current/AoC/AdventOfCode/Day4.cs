using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class Day4
    {
        public Day4()
        {

        }

        public void Run()
        {
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day4.txt");
            //string[] lines = { "[1518-09-14 00:54] wakes up", "[1518-04-15 23:58] Guard #373 begins shift", "[1518-07-25 00:53] wakes up" };

            List<TimeStamp> timestamps = new List<TimeStamp>();
            var regex2 = new Regex(@"\[(\d*)-(\d*)-(\d*)\s(\d*):(\d*)\]\s([a-zA-Z]*\s?(\#[0-9]*)?[a-zA-Z\s]*)");

            foreach (string line in lines)
            {
                Match mm = regex2.Match(line);

                timestamps.Add(new TimeStamp()
                {
                    year = Int32.Parse(mm.Groups[1].ToString()),
                    month = Int32.Parse(mm.Groups[2].ToString()),
                    day = Int32.Parse(mm.Groups[3].Value),
                    hour = Int32.Parse(mm.Groups[4].Value),
                    minute = Int32.Parse(mm.Groups[5].Value),
                    info = mm.Groups[6].Value,
                    guardId = ((mm.Groups.Count == 8 && mm.Groups[7].Length != 0) ? Int32.Parse(mm.Groups[7].Value.TrimStart('#')) : 0)
                });
            }

            List<TimeStamp> sorted = new List<TimeStamp>();

            for (int i = 0; i < timestamps.Count; i++)
            {
                if (sorted.Count == 0)
                {
                    sorted.Insert(0, timestamps[i]);
                    continue;
                }

                for (int j = sorted.Count - 1; j >= 0; j--)
                {
                    if (timestamps[i].GreaterThan(sorted[j]))
                    {
                        sorted.Insert(j + 1, timestamps[i]);
                        break;
                    }
                    if (j == 0)
                        sorted.Insert(0, timestamps[i]);
                }
            }

            // Update info with guard id
            List<TimeStamp> updatedList = new List<TimeStamp>();
            int currentGuardId = 0;
            foreach (var item in sorted)
            {
                if (item.guardId != 0)
                    currentGuardId = item.guardId;
                updatedList.Add(new TimeStamp() { year = item.year, month = item.month, day = item.day, hour = item.hour, minute = item.minute, info = item.info, guardId = currentGuardId });
            }
            foreach (var item in updatedList)
            {
                item.Print();
            }

            string FALLSASLEEP = "falls asleep";
            string WAKESUP = "wakes up";
            string BEGINSSHIFT = "begins shift";
            string ENDSSHIFT = "ends shift";

            Dictionary<int, int> guardSleepTimes = new Dictionary<int, int>();
            int currentGuard = 0;
            int fallsAsleep = 0;
            foreach (var item in updatedList)
            {
                if (item.info.Contains(BEGINSSHIFT))
                {
                    currentGuard = item.guardId;
                    if (!guardSleepTimes.ContainsKey(currentGuard))
                    {
                        guardSleepTimes[currentGuard] = 0;
                    }
                }
                else if (item.info.Contains(ENDSSHIFT))
                {
                    currentGuard = 0;
                }
                else if (item.info.Contains(FALLSASLEEP))
                {
                    fallsAsleep = item.minute;
                }
                else if (item.info.Contains(WAKESUP))
                {
                    guardSleepTimes[currentGuard] += (item.minute - fallsAsleep);
                }
                //Console.WriteLine("Guard on duty = {0}", currentGuard);

            }

            int maxSleepTime = 0;
            int guardId = 0;
            foreach (var item in guardSleepTimes)
            {
                //Console.WriteLine("Guard {0} slept for {1}", item.Key, item.Value);
                if (item.Value > maxSleepTime)
                {
                    maxSleepTime = item.Value;
                    guardId = item.Key;
                }
            }

            Console.WriteLine("\nGuard {0} slept the longest {1}", guardId, maxSleepTime);

            List<TimeStamp> guardInfo = new List<TimeStamp>();
            foreach (var item in updatedList)
            {
                if (item.guardId == guardId)
                {
                    guardInfo.Add(item);
                }
            }

            foreach (var item in guardInfo)
            {
                item.Print();
            }

            int[] mins = new int[60];

            int wakesup = 0;
            foreach (var item in guardInfo)
            {
                if (item.info.Contains(FALLSASLEEP))
                {
                    fallsAsleep = item.minute;
                }
                else if (item.info.Contains(WAKESUP))
                {
                    wakesup = item.minute;
                    for (int i = fallsAsleep; i < wakesup; i++)
                    {
                        mins[i]++;
                    }
                }
            }

            int maxMin = 0;
            int maxMinVal = 0;
            for (int i = 0; i < 60; i++)
            {
                Console.WriteLine("{0} {1}", i, mins[i]);
                if (mins[i] > maxMinVal)
                {
                    maxMinVal = mins[i];
                    maxMin = i;
                }
            }

            Console.WriteLine("\nGuard {0} slept for {1} at {2} minute ==> ANSWER {3}", guardId, maxMinVal, maxMin, guardId * maxMin);


            // PART 2
            Dictionary<int, Dictionary<int, int>> guardToMins = new Dictionary<int, Dictionary<int, int>>();

            foreach (var item in updatedList)
            {
                if (item.info.Contains(FALLSASLEEP))
                {
                    fallsAsleep = item.minute;
                    if (guardToMins.ContainsKey(item.guardId) == false)
                    {
                        guardToMins[item.guardId] = new Dictionary<int, int>();
                        for (int i = 0; i < 60; i++)
                        {
                            guardToMins[item.guardId][i] = 0;
                        }
                    }
                }
                else if (item.info.Contains(WAKESUP))
                {
                    wakesup = item.minute;
                    for (int i = fallsAsleep; i < wakesup; i++)
                    {
                        guardToMins[item.guardId][i] = guardToMins[item.guardId][i] + 1;
                    }
                }
            }

            int longestMin = 0;
            int longestMinValue = 0;
            int longestGuardId = 0;
            foreach (var item in guardToMins)
            {
                //    Console.Write("Guard {0} ", item.Key);
                foreach (var litem in item.Value)
                {
                    //        Console.Write( " {0}", litem);
                    if (litem.Value > longestMinValue)
                    {
                        longestMinValue = litem.Value;
                        longestMin = litem.Key;
                        longestGuardId = item.Key;

                        Console.WriteLine("Guard {0} slept {1} times on minute {2}", longestGuardId, longestMinValue, longestMin);
                    }
                }
                //    Console.WriteLine();
            }

            Console.WriteLine("Guard {0} slept {1} in minute {2} ANSWER 2 {3}", longestGuardId, longestMinValue, longestMin, longestGuardId * longestMin);

        }
    }
}
