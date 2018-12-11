using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class Day5
    {
        public Day5()
        {

        }

        public void Run()
        {
            Stack<char> cstack = new Stack<char>();

            string[] lines = System.IO.File.ReadAllLines(@"..\..\day5.txt");
            foreach (var s in lines)
            {
                foreach (char c in s)
                {
                    cstack.Push(c);
                    if (cstack.Count == 1)
                        continue;

                    bool b = true;
                    while (b)
                    {
                        if (cstack.Count <= 1)
                            break;

                        if (Char.ToUpper(c) == c)
                        {
                            char cc = cstack.Pop();
                            // c is upper case
                            if (cstack.First() == Char.ToLower(c))
                            {
                                cstack.Pop();
                                break; ;
                            }
                            cstack.Push(cc);
                        }
                        else if (Char.ToLower(c) == c)
                        {
                            char cc = cstack.Pop();
                            // c is lower case
                            if (cstack.First() == Char.ToUpper(c))
                            {
                                cstack.Pop();
                                break;
                            }
                            cstack.Push(cc);
                        }
                        b = false;
                    }
                }
            }

            string answer = string.Empty;
            foreach (var item in cstack)
            {
                answer += item;
            }
            Console.WriteLine("PART 1 ANSWER {0}", cstack.Count);


            char[] alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ".ToCharArray();

            int minlen = int.MaxValue;
            foreach (var s in lines)
            {

                foreach (char character in alpha)
                {
                    cstack.Clear();
                    foreach (char c in s)
                    {
                        if (Char.ToUpper(c) == character)
                            continue;

                        cstack.Push(c);
                        if (cstack.Count == 1)
                            continue;

                        bool b = true;
                        while (b)
                        {
                            if (cstack.Count <= 1)
                                break;

                            if (Char.ToUpper(c) == c)
                            {
                                char cc = cstack.Pop();
                                // c is upper case
                                if (cstack.First() == Char.ToLower(c))
                                {
                                    cstack.Pop();
                                    break; ;
                                }
                                cstack.Push(cc);
                            }
                            else if (Char.ToLower(c) == c)
                            {
                                char cc = cstack.Pop();
                                // c is lower case
                                if (cstack.First() == Char.ToUpper(c))
                                {
                                    cstack.Pop();
                                    break;
                                }
                                cstack.Push(cc);
                            }
                            b = false;
                        }
                    }
                    if (cstack.Count < minlen)
                    {
                        minlen = cstack.Count;
                    }
                }
            }

            Console.WriteLine("Min length is {0}", minlen);

        }
    }
}
