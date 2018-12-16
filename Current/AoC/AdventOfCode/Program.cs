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

    public static class Helper
    {
        public static int ManhattanDistance(int x1, int x2, int y1, int y2)
        {
            return Math.Abs(x1 - x2) + Math.Abs(y1 - y2);
        }

    }

    public class Coord
    {
        public int x;
        public int y;
    }

    public class CoordInfo : Coord
    {
        public int id;
    }

    public class Grid
    {
        public int closestCoord;
        public int distance;
    }

    class Program
    {

        static void Main(string[] args)
        {
            #region DAY1

            //Day1 day1 = new Day1();
            //day1.Run();

            #endregion

            #region DAY2

            //Day2 day2 = new Day2();
            //day2.Run();

            #endregion

            #region DAY3

            //Day3 day3 = new Day3();
            //day3.Run();

            #endregion

            #region DAY4

            //Day4 day4 = new Day4();
            //day4.Run();

            #endregion

            #region DAY5

            //Day5 day5 = new Day5();
            //day5.Run();

            #endregion

            #region DAY6

            //Day6 day6 = new Day6();
            //day6.Run();

            #endregion

            #region DAY7

            //Day7 day7 = new Day7();
            //day7.Run();

            #endregion

            #region DAY8

            //Day8 day8 = new Day8();
            //day8.Run();

            #endregion

            #region DAY9

            //Day9 day9 = new Day9();
            //day9.Run();

            #endregion

            #region DAY10

            //Day10 day10 = new Day10();
            //day10.Run();

            #endregion

            #region DAY11

            //Day11 day11 = new Day11();
            //day11.Run();

            #endregion

            #region DAY12

            //Day12 day12 = new Day12();
            //day12.Run();

            #endregion

            #region DAY13

            //Day13 day13 = new Day13();
            //day13.Run();

            #endregion

            #region DAY14

            //Day14 day14 = new Day14();
            //day14.Run();

            #endregion

            #region DAY15

            Day15 day15 = new Day15();
            day15.Run();

            #endregion

            #region DAY16
            #endregion

            #region DAY17
            #endregion

            #region DAY18
            #endregion

            #region DAY19
            #endregion

            #region DAY20
            #endregion

            #region DAY21
            #endregion

            #region DAY22
            #endregion

            #region DAY23
            #endregion

            #region DAY24
            #endregion

            #region DAY25
            #endregion

            #region DAY26
            #endregion

            #region DAY27
            #endregion

            #region DAY28
            #endregion

            #region DAY29
            #endregion

            #region DAY30
            #endregion

            #region DAY31
            #endregion
        }
    }
}


