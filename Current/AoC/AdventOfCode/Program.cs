using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace AdventOfCode
{
    struct Data
    {
        public int id;
        public int fromleft;
        public int fromtop;
        public int width;
        public int height;
        public string info;
        public void Print()
        {
            Console.WriteLine("ID {0}\tFrom Left {1}\tFrom Top {2}\tWidth {3}\tHeight {4}", id, fromleft, fromtop, width, height);
        }
    }

    struct TimeStamp
    {
        public int year;
        public int month;
        public int day;
        public int hour;
        public int minute;
        public int guardId;
        public string info;

        public bool EqualTo(TimeStamp rval)
        {
            if (year != rval.year)
                return false;
            if (month != rval.month)
                return false;
            if (day != rval.day)
                return false;
            if (hour != rval.hour)
                return false;
            if (minute != rval.minute)
                return false;
            return true;
        }
        public bool GreaterThan(TimeStamp rval)
        {
            if (EqualTo(rval))
                return false;
            return !LessThan(rval);
        }
        public bool LessThan(TimeStamp rval)
        {
            if (EqualTo(rval))
                return false;

            DateTime l = new DateTime(year, month, day, hour, minute, 0);
            DateTime r = new DateTime(rval.year, rval.month, rval.day, rval.hour, rval.minute, 0);
            return (l < r);
        }
        public void Print()
        {
            Console.WriteLine("Year {0} Month {1} Day {2} Hour {3} Minute {4} Info {5}\t\tGuard Id {6}", year, month, day, hour, minute, info, guardId);
        }
    }

    public class Helper
    {
        public int RemoveDups(ref Stack<char> cstack)
        {
            int numPops = 0;
            Stack<char> newstack = new Stack<char>();
            foreach (char c in cstack)
            {
                newstack.Push(c);
                bool b = true;
                while (b)
                {
                    if (newstack.Count <= 1)
                        break;

                    if (Char.ToUpper(c) == c)
                    {
                        char cc = newstack.Pop();
                        // c is upper case
                        if (newstack.First() == Char.ToLower(c))
                        {
                            newstack.Pop();
                            numPops++;
                            continue;
                        }
                        newstack.Push(cc);
                    }
                    else if (Char.ToLower(c) == c)
                    {
                        char cc = newstack.Pop();
                        // c is lower case
                        if (newstack.First() == Char.ToUpper(c))
                        {
                            newstack.Pop();
                            numPops++;
                            continue;
                        }
                        newstack.Push(cc);
                    }
                    b = false;
                }
            }
            cstack = newstack;
            return numPops;
        }

    }


    class Program
    {
        
        static void Main(string[] args)
        {
            #region DAY1
            /*
            int[] fullList = {+5,
-11,
-1,
-16,
+12,
+9,
-15,
+20,
+4,
+17,
-4,
-14,
+6,
-17,
+6,
-19,
-12,
+17,
-6,
-18,
+1,
+15,
-14,
+10,
-4,
-2,
+5,
+6,
+8,
+3,
+17,
-9,
+18,
-1,
+17,
-15,
+7,
-6,
-17,
-17,
+19,
+19,
-13,
+18,
-15,
+16,
+7,
-10,
-5,
+22,
+8,
-13,
+4,
+3,
+19,
+17,
-19,
-1,
-11,
+2,
+1,
-13,
+1,
+3,
-14,
+16,
-9,
+19,
+13,
-20,
+6,
+22,
+10,
+6,
+15,
-13,
-13,
-8,
+16,
+20,
-5,
+1,
+7,
+11,
-13,
+5,
-16,
-2,
-4,
+25,
-5,
-10,
-12,
-9,
+16,
-2,
-19,
-3,
-12,
+5,
+17,
+16,
+11,
+16,
+10,
+4,
+3,
+11,
-12,
+19,
+3,
+17,
+15,
-6,
-6,
-4,
+3,
+10,
+8,
+15,
-7,
+13,
+3,
+6,
+2,
+16,
+20,
+3,
-11,
+3,
-11,
+12,
+6,
+3,
+11,
+5,
+2,
+12,
-4,
-2,
+4,
+3,
-4,
+20,
+1,
+19,
+14,
+5,
-16,
-15,
-16,
-4,
-10,
-13,
-10,
-18,
+10,
-6,
-7,
-3,
-2,
-14,
+12,
-2,
-6,
-11,
-5,
-6,
+20,
-11,
-1,
+9,
-1,
+5,
+6,
+11,
-19,
-9,
-14,
-4,
-6,
-1,
+2,
-6,
-12,
+20,
-12,
-13,
-9,
-3,
-7,
-17,
+14,
-9,
+20,
-4,
-8,
-1,
-6,
+16,
+6,
-18,
-12,
+6,
-22,
-15,
+10,
+6,
+20,
-16,
+1,
-18,
+4,
+19,
+9,
-17,
+1,
+13,
+21,
+23,
-4,
+7,
-16,
+3,
-4,
-3,
-17,
-20,
-10,
-20,
+16,
+3,
+14,
-11,
+3,
-29,
-1,
+7,
-18,
+5,
-7,
-16,
+6,
-7,
-15,
+9,
+22,
-2,
-21,
-18,
+1,
+10,
+13,
+13,
-24,
-6,
-22,
-10,
+9,
+4,
-8,
-16,
+3,
-5,
-19,
-6,
-11,
+3,
-8,
-16,
-14,
-16,
-15,
-6,
+3,
+13,
+8,
-19,
-18,
-8,
+9,
-15,
-14,
-2,
+18,
-17,
+2,
+18,
-6,
-3,
-19,
+16,
-4,
+6,
+21,
-6,
+7,
+17,
-8,
-4,
+6,
+19,
-2,
+5,
+20,
-3,
-6,
+5,
+5,
-17,
-18,
+16,
+4,
+7,
+6,
+8,
+6,
-1,
+10,
-13,
-4,
-10,
+8,
-14,
+17,
+9,
+2,
-7,
-22,
-16,
+20,
-13,
+8,
-17,
+1,
+19,
+14,
+19,
+11,
-6,
+25,
+18,
+19,
+5,
+20,
+17,
+4,
-10,
+47,
+4,
-1,
+23,
+24,
-8,
-10,
+31,
+19,
-11,
-17,
+8,
-24,
+9,
+32,
+18,
-1,
+4,
-13,
+4,
+17,
-2,
+11,
+11,
+4,
-3,
-3,
+22,
+19,
+14,
-21,
+13,
+9,
-14,
-16,
+20,
+16,
-14,
+5,
-15,
+12,
-11,
+1,
+3,
-24,
-9,
-9,
-22,
-12,
-10,
-7,
-3,
+12,
+13,
+17,
-11,
+35,
+12,
-9,
+16,
+22,
-18,
-18,
+19,
-8,
+23,
+19,
+3,
+8,
+15,
-2,
+11,
+14,
+10,
+15,
+8,
-1,
+13,
+1,
+18,
-11,
+4,
+4,
+11,
+9,
-18,
-9,
+13,
-18,
+10,
+3,
-6,
-5,
-10,
-11,
-14,
-2,
-9,
+3,
-4,
-6,
+13,
-2,
-17,
-4,
+7,
+6,
-12,
-7,
+14,
-6,
-18,
+19,
-18,
-2,
-13,
+6,
-15,
+14,
+7,
+9,
-14,
+9,
-19,
+1,
+13,
-2,
-10,
-11,
+13,
-6,
-6,
+19,
+10,
+17,
-8,
-7,
+19,
+16,
-1,
+7,
+16,
-15,
-17,
+12,
+16,
-2,
+14,
-3,
-16,
-17,
-5,
+16,
+29,
-3,
-2,
+13,
-18,
+15,
-4,
-14,
-12,
-16,
-19,
+39,
-9,
+19,
+3,
-11,
+10,
+12,
+19,
-4,
+12,
+13,
+19,
+3,
-19,
+9,
-16,
+10,
+18,
+12,
-6,
-2,
-11,
+20,
+15,
+15,
+4,
+12,
-38,
+9,
+33,
+24,
+6,
+4,
-36,
-47,
-15,
-13,
-3,
+1,
+12,
+14,
+9,
-32,
+7,
-16,
-5,
-29,
+12,
-2,
+15,
-12,
-11,
-39,
-40,
+3,
-34,
-5,
+78,
+4,
+52,
+1,
+90,
+112,
+152,
-80,
+81800,
-18,
+15,
-9,
+11,
+2,
-5,
+16,
-5,
+15,
-1,
+2,
-14,
-7,
+12,
-10,
-9,
+20,
+14,
-9,
+12,
+9,
+13,
+3,
+11,
+14,
-3,
+10,
+8,
+12,
+5,
+10,
+1,
+14,
-5,
+1,
-4,
-13,
+9,
+18,
+17,
+16,
+9,
-1,
-10,
+13,
+13,
+11,
-18,
+15,
-9,
-13,
+3,
+1,
+11,
-3,
-10,
+19,
-11,
+13,
+12,
-8,
-10,
-6,
+13,
+5,
-13,
-7,
-1,
+18,
+7,
+14,
-2,
+5,
+1,
+16,
-7,
+18,
+13,
-6,
+18,
-1,
+12,
-4,
-10,
+7,
-15,
-9,
-7,
-7,
-6,
+11,
-16,
+7,
-4,
+11,
-4,
-6,
-14,
+1,
+6,
-3,
+2,
+21,
+12,
-16,
+18,
-5,
+17,
+4,
+19,
+6,
-13,
+17,
-3,
-2,
-17,
+7,
-3,
-7,
+14,
+17,
+8,
+7,
-17,
+18,
-15,
-4,
+7,
+2,
+1,
-14,
-1,
-6,
+9,
-10,
-4,
+15,
-14,
-18,
-14,
-9,
-11,
+9,
+3,
+12,
+1,
+3,
-10,
-15,
+7,
+6,
+13,
+9,
+7,
-4,
+9,
-14,
+21,
-9,
+24,
+10,
+6,
+6,
-19,
+22,
-10,
-18,
+10,
+14,
-4,
+3,
+7,
+14,
+11,
+16,
-10,
+11,
-9,
-5,
-6,
-2,
-15,
+3,
-16,
+19,
+8,
+2,
-17,
+3,
+5,
+14,
-16,
-4,
-5,
+1,
-3,
+4,
+6,
+18,
+16,
+4,
-18,
+6,
+10,
-6,
+1,
+6,
+9,
+17,
-8,
-15,
-12,
+1,
-6,
+4,
+12,
+2,
+17,
-9,
-7,
+10,
+12,
+17,
+8,
+15,
+7,
-18,
-1,
+4,
+13,
-3,
+16,
+4,
+2,
-8,
-5,
+14,
+10,
+18,
-15,
+19,
-11,
-4,
-16,
+13,
+16,
-15,
+10,
-20,
-7,
-15,
-10,
-2,
-6,
+19,
-3,
-9,
-18,
+12,
-8,
+3,
+13,
+20,
+18,
-16,
+15,
+12,
+1,
-18,
+10,
-14,
-17,
-7,
-9,
-20,
+8,
-9,
+7,
-11,
-19,
+7,
-14,
+6,
+4,
+14,
+8,
-11,
+2,
-1,
-19,
+16,
+9,
-10,
+20,
+12,
+11,
+13,
-3,
-2,
+3,
-20,
+6,
-17,
+3,
-9,
-6,
-16,
+7,
+7,
-23,
-6,
+14,
-3,
-31,
-18,
-19,
-12,
-26,
+23,
+9,
-7,
-10,
+22,
+17,
+17,
-7,
-8,
+9,
+28,
+5,
+24,
-28,
+36,
+37,
+7,
+12,
+19,
+15,
-3,
-20,
+17,
+18,
+4,
-8,
+9,
-4,
-2,
-19,
+11,
-1,
+3,
-7,
+8,
+9,
-8,
+19,
+9,
+12,
-11,
-5,
-13,
+9,
-6,
+7,
+17,
-13,
+16,
+10,
-5,
+20,
+6,
-1,
+17,
-14,
+10,
+18,
-1,
+3,
-10,
-4,
-10,
-10,
-16,
-2,
+7,
+16,
-12,
+6,
+8,
+22,
+7,
-6,
-13,
-14,
+10,
-1,
-21,
-1,
+8,
-15,
+9,
-17,
-2,
-21,
+4,
-19,
-13,
-8,
+26,
+4,
-27,
-8,
+2,
+30,
-11,
-82484};
            List<int> frequencies = new List<int>();
            frequencies.Add(0);
            int currentFrequecy = 0;
            bool found = false;
            while (!found)
            {
                foreach (int item in fullList)
                {
                    //Console.WriteLine("Frequency is {0}   item is {1}", currentFrequecy, item);
                    currentFrequecy += item;
                    if (frequencies.Contains(currentFrequecy) == true)
                    {
                        Console.WriteLine("Found match {0}", currentFrequecy);
                        found = true;
                        break;
                    }

                    frequencies.Add(currentFrequecy);
                }
                                
            }
            */
            #endregion

            #region DAY2

            //int twiceCount = 0;
            //int thriceCount = 0;
            //string[] lines = System.IO.File.ReadAllLines(@"..\..\day2.txt");
            //foreach (string line in lines)
            //{
            //    Dictionary<char, int> counts = new Dictionary<char, int>();
            //    foreach (char c in line)
            //    {
            //        if (counts.ContainsKey(c))
            //            continue;
            //        int count = line.Count(f => f == c);
            //        counts.Add(c, count);
            //    }

            //    if (counts.ContainsValue(2))
            //        twiceCount++;
            //    if (counts.ContainsValue(3))
            //        thriceCount++;
            //    counts.Clear();
            //    // Use a tab to indent each line of the file.
            //    //Console.WriteLine("\t" + line);
            //}

            //Console.WriteLine("Checksum = {0}", twiceCount * thriceCount);


            //for (int i = 0; i < lines.Count(); i++)
            //{

            //    var linelen = lines[i].Count();

            //    for (int j = i + 1; j < lines.Count(); j++)
            //    {
            //        int nummissed = 0;
            //        for (int k = 0; k < linelen; k++)
            //        {
            //            if (lines[i][k] != lines[j][k])
            //                nummissed++;
            //            if (nummissed == 3)
            //                break;
            //            if (k == linelen - 1)
            //            {
            //                Console.WriteLine("Found match {0} {1}", lines[i], lines[j]);
            //            }

            //        }
            //    }
            //}

            #endregion

            #region DAY3

            /*
            #1 @ 1,3: 4x4
            #2 @ 3,1: 4x4
            #3 @ 5,5: 2x2 
            */

            //int matrixwidth = 1000;
            //int matrixheight = 1000;
            //int[,] matrix = new int[matrixwidth, matrixheight];

            //Dictionary<int, Data> input = new Dictionary<int, Data>();
            //char[] delimiterChars = { '@', ':', ',', 'x' };
            //string[] lines = System.IO.File.ReadAllLines(@"..\..\day3.txt");

            //foreach (string line in lines)
            //{
            //    string[] d = line.Split(delimiterChars);
            //    //Console.WriteLine("Line {0} has {1} pieces", line, d.Length);
            //    Data s = new Data();
            //    s.id = Int32.Parse(d[0].Trim('#'));
            //    s.fromleft = Int32.Parse(d[1].Trim(' '));
            //    s.fromtop = Int32.Parse(d[2].Trim(' '));
            //    s.width = Int32.Parse(d[3].Trim(' '));
            //    s.height = Int32.Parse(d[4].Trim(' '));
            //    input[s.id] = s;
            //}

            //foreach (var item in input)
            //{
            //    int xpos = item.Value.fromleft;
            //    int ypos = item.Value.fromtop;
            //    for (int i = 0; i < item.Value.width; i++)
            //    {
            //        for (int j = 0; j < item.Value.height; j++)
            //        {
            //            matrix[i + xpos, j + ypos]++;
            //        }
            //    }
            //}

            //int overlaps = 0;
            //for (int i = 0; i < matrixheight; i++)
            //{
            //    for (int j = 0; j < matrixwidth; j++)
            //    {
            //        //if (matrix[j, i] == 0)
            //        //    Console.Write('.');
            //        //else
            //        //    Console.Write(matrix[j, i]);
            //        if (matrix[j, i] > 1)
            //            overlaps++;
            //    }
            //}
            //Console.WriteLine("Overlaps = {0}", overlaps);

            //int overlapid = -1;
            //foreach (var item in input)
            //{
            //    bool boverlaps = false;
            //    int xpos = item.Value.fromleft;
            //    int ypos = item.Value.fromtop;
            //    for (int i = 0; i < item.Value.width; i++)
            //    {
            //        for (int j = 0; j < item.Value.height; j++)
            //        {
            //            if(matrix[i + xpos, j + ypos] != 1)
            //            {
            //                boverlaps = true;
            //                break;
            //            }
            //        }
            //        if (boverlaps)
            //            break;
            //    }
            //    if (boverlaps)
            //        continue;
            //    overlapid = item.Value.id;
            //}
            //Console.WriteLine("Id with no overlaps {0}", overlapid);
            #endregion

            #region DAY4

            //string[] lines = System.IO.File.ReadAllLines(@"..\..\day4.txt");
            ////string[] lines = { "[1518-09-14 00:54] wakes up", "[1518-04-15 23:58] Guard #373 begins shift", "[1518-07-25 00:53] wakes up" };

            //List<TimeStamp> timestamps = new List<TimeStamp>();
            //var regex2 = new Regex(@"\[(\d*)-(\d*)-(\d*)\s(\d*):(\d*)\]\s([a-zA-Z]*\s?(\#[0-9]*)?[a-zA-Z\s]*)");

            //foreach (string line in lines)
            //{
            //    Match mm = regex2.Match(line);

            //    timestamps.Add(new TimeStamp()
            //    {
            //        year = Int32.Parse(mm.Groups[1].ToString()),
            //        month = Int32.Parse(mm.Groups[2].ToString()),
            //        day = Int32.Parse(mm.Groups[3].Value),
            //        hour = Int32.Parse(mm.Groups[4].Value),
            //        minute = Int32.Parse(mm.Groups[5].Value),
            //        info = mm.Groups[6].Value,
            //        guardId = ((mm.Groups.Count == 8 && mm.Groups[7].Length != 0) ? Int32.Parse(mm.Groups[7].Value.TrimStart('#')) : 0)
            //    });
            //}

            //List<TimeStamp> sorted = new List<TimeStamp>();

            //for (int i = 0; i < timestamps.Count; i++)
            //{
            //    if (sorted.Count == 0)
            //    {
            //        sorted.Insert(0, timestamps[i]);
            //        continue;
            //    }

            //    for (int j = sorted.Count - 1; j >= 0; j--)
            //    {
            //        if (timestamps[i].GreaterThan(sorted[j]))
            //        {
            //            sorted.Insert(j + 1, timestamps[i]);
            //            break;
            //        }
            //        if (j == 0)
            //            sorted.Insert(0, timestamps[i]);
            //    }
            //}

            //// Update info with guard id
            //List<TimeStamp> updatedList = new List<TimeStamp>();
            //int currentGuardId = 0;
            //foreach (var item in sorted)
            //{
            //    if (item.guardId != 0)
            //        currentGuardId = item.guardId;
            //    updatedList.Add(new TimeStamp() { year = item.year, month = item.month, day = item.day, hour = item.hour, minute = item.minute, info = item.info, guardId = currentGuardId });
            //}
            //foreach (var item in updatedList)
            //{
            //    item.Print();
            //}

            //string FALLSASLEEP = "falls asleep";
            //string WAKESUP = "wakes up";
            //string BEGINSSHIFT = "begins shift";
            //string ENDSSHIFT = "ends shift";

            //Dictionary<int, int> guardSleepTimes = new Dictionary<int, int>();
            //int currentGuard = 0;
            //int fallsAsleep = 0;
            //foreach (var item in updatedList)
            //{
            //    if (item.info.Contains(BEGINSSHIFT))
            //    {
            //        currentGuard = item.guardId;
            //        if (!guardSleepTimes.ContainsKey(currentGuard))
            //        {
            //            guardSleepTimes[currentGuard] = 0;
            //        }
            //    }
            //    else if (item.info.Contains(ENDSSHIFT))
            //    {
            //        currentGuard = 0;
            //    }
            //    else if (item.info.Contains(FALLSASLEEP))
            //    {
            //        fallsAsleep = item.minute;
            //    }
            //    else if (item.info.Contains(WAKESUP))
            //    {
            //        guardSleepTimes[currentGuard] += (item.minute - fallsAsleep);
            //    }
            //    //Console.WriteLine("Guard on duty = {0}", currentGuard);

            //}

            //int maxSleepTime = 0;
            //int guardId = 0;
            //foreach (var item in guardSleepTimes)
            //{
            //    //Console.WriteLine("Guard {0} slept for {1}", item.Key, item.Value);
            //    if (item.Value > maxSleepTime)
            //    {
            //        maxSleepTime = item.Value;
            //        guardId = item.Key;
            //    }
            //}

            //Console.WriteLine("\nGuard {0} slept the longest {1}", guardId, maxSleepTime);

            //List<TimeStamp> guardInfo = new List<TimeStamp>();
            //foreach (var item in updatedList)
            //{
            //    if (item.guardId == guardId)
            //    {
            //        guardInfo.Add(item);
            //    }
            //}

            //foreach (var item in guardInfo)
            //{
            //    item.Print();
            //}

            //int[] mins = new int[60];

            //int wakesup = 0;
            //foreach (var item in guardInfo)
            //{
            //    if (item.info.Contains(FALLSASLEEP))
            //    {
            //        fallsAsleep = item.minute;
            //    }
            //    else if (item.info.Contains(WAKESUP))
            //    {
            //        wakesup = item.minute;
            //        for (int i = fallsAsleep; i < wakesup; i++)
            //        {
            //            mins[i]++;
            //        }
            //    }
            //}

            //int maxMin = 0;
            //int maxMinVal = 0;
            //for (int i = 0; i < 60; i++)
            //{
            //    Console.WriteLine("{0} {1}", i, mins[i]);
            //    if (mins[i] > maxMinVal)
            //    {
            //        maxMinVal = mins[i];
            //        maxMin = i;
            //    }
            //}

            //Console.WriteLine("\nGuard {0} slept for {1} at {2} minute ==> ANSWER {3}", guardId, maxMinVal, maxMin, guardId * maxMin);


            //// PART 2
            //Dictionary<int, Dictionary<int, int>> guardToMins = new Dictionary<int, Dictionary<int, int>>();

            //foreach (var item in updatedList)
            //{
            //    if (item.info.Contains(FALLSASLEEP))
            //    {
            //        fallsAsleep = item.minute;
            //        if (guardToMins.ContainsKey(item.guardId) == false)
            //        {
            //            guardToMins[item.guardId] = new Dictionary<int, int>();
            //            for (int i = 0; i < 60; i++)
            //            {
            //                guardToMins[item.guardId][i] = 0;
            //            }
            //        }
            //    }
            //    else if (item.info.Contains(WAKESUP))
            //    {
            //        wakesup = item.minute;
            //        for (int i = fallsAsleep; i < wakesup; i++)
            //        {
            //            guardToMins[item.guardId][i] = guardToMins[item.guardId][i]+1;
            //        }
            //    }
            //}

            //int longestMin = 0;
            //int longestMinValue = 0;
            //int longestGuardId = 0;
            //foreach (var item in guardToMins)
            //{
            ////    Console.Write("Guard {0} ", item.Key);
            //    foreach (var litem in item.Value)
            //    {
            ////        Console.Write( " {0}", litem);
            //        if( litem.Value > longestMinValue)
            //        {
            //            longestMinValue = litem.Value;
            //            longestMin = litem.Key;
            //            longestGuardId = item.Key;

            //            Console.WriteLine("Guard {0} slept {1} times on minute {2}", longestGuardId, longestMinValue, longestMin);
            //        }
            //    }
            ////    Console.WriteLine();
            //}

            //Console.WriteLine("Guard {0} slept {1} in minute {2} ANSWER 2 {3}", longestGuardId, longestMinValue, longestMin, longestGuardId * longestMin);
            #endregion

            #region DAY5

            //Stack<char> cstack = new Stack<char>();

            //string[] lines = System.IO.File.ReadAllLines(@"..\..\day5.txt");
            //foreach (var s in lines)
            //{
            //    foreach (char c in s)
            //    {
            //        cstack.Push(c);
            //        if (cstack.Count == 1)
            //            continue;

            //        bool b = true;
            //        while (b)
            //        {
            //            if (cstack.Count <= 1)
            //                break;

            //            if (Char.ToUpper(c) == c)
            //            {
            //                char cc = cstack.Pop();
            //                // c is upper case
            //                if (cstack.First() == Char.ToLower(c))
            //                {
            //                    cstack.Pop();
            //                    break; ;
            //                }
            //                cstack.Push(cc);
            //            }
            //            else if (Char.ToLower(c) == c)
            //            {
            //                char cc = cstack.Pop();
            //                // c is lower case
            //                if (cstack.First() == Char.ToUpper(c))
            //                {
            //                    cstack.Pop();
            //                    break;
            //                }
            //                cstack.Push(cc);
            //            }
            //            b = false;
            //        }
            //    }
            //}

            ////Helper h = new Helper();
            ////while(h.RemoveDups(ref cstack) != 0 )
            ////{

            ////}
            //string answer = string.Empty;
            //foreach (var item in cstack)
            //{
            //    answer += item;
            //}
            //Console.WriteLine("PART 1 ANSWER {0}", cstack.Count);


            //char[] alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ".ToCharArray();

            //int minlen = int.MaxValue;
            //foreach (var s in lines)
            //{

            //    foreach (char character in alpha)
            //    {
            //        cstack.Clear();
            //        foreach (char c in s)
            //        {
            //            if (Char.ToUpper(c) == character)
            //                continue;

            //            cstack.Push(c);
            //            if (cstack.Count == 1)
            //                continue;

            //            bool b = true;
            //            while (b)
            //            {
            //                if (cstack.Count <= 1)
            //                    break;

            //                if (Char.ToUpper(c) == c)
            //                {
            //                    char cc = cstack.Pop();
            //                    // c is upper case
            //                    if (cstack.First() == Char.ToLower(c))
            //                    {
            //                        cstack.Pop();
            //                        break; ;
            //                    }
            //                    cstack.Push(cc);
            //                }
            //                else if (Char.ToLower(c) == c)
            //                {
            //                    char cc = cstack.Pop();
            //                    // c is lower case
            //                    if (cstack.First() == Char.ToUpper(c))
            //                    {
            //                        cstack.Pop();
            //                        break;
            //                    }
            //                    cstack.Push(cc);
            //                }
            //                b = false;
            //            }
            //        }
            //        if(cstack.Count < minlen)
            //        {
            //            minlen = cstack.Count;
            //        }
            //    }
            //}

            //Console.WriteLine("Min length is {0}", minlen);

            #endregion

            #region DAY6

            string[] lines = System.IO.File.ReadAllLines(@"..\..\day6.txt");

            #endregion
        }
    }
}

