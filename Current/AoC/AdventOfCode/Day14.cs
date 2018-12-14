using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class Day14
    {
        public Day14()
        {
            _recipes = new List<int>() { 3, 7 };

            _elf1idx = 0;
            _elf2idx = 1;
        }

        public void Run()
        {
            int targetnum = 503761;
            List<int> target = new List<int>() { 5, 0, 3, 7, 6, 1 };
            int numdigits = target.Count;
            int nummatches = 0;

            //int target = 793061;
            //while(_recipes.Count < target+10)       // Part 1
            //while (CheckForRecipe(targetnum) == false)     // Part 2
            while(true)
            {
                if (_recipes.Count == (targetnum + 10))
                {
                    Console.Write("Part 1:  ");

                    int start = _recipes.Count - 10;
                    for (int i = start; i < _recipes.Count; i++)
                    {
                        Console.Write(_recipes[i]);
                    }
                    Console.WriteLine();
                }
                //PrintScores();
                int score = _recipes[_elf1idx] + _recipes[_elf2idx];
                int newscore1 = 0;
                int newscore2 = 0;

                if (score >= 10)
                {
                    score -= 10;
                    newscore1 = 1;
                    newscore2 = score;
                    _recipes.Add(newscore1);

                    if (target[nummatches] == newscore1)
                        nummatches++;
                    else
                        nummatches = 0;

                    if (nummatches != numdigits)
                    {
                        _recipes.Add(newscore2);
                        if (target[nummatches] == newscore2)
                            nummatches++;
                        else if (nummatches > 0)
                        {
                            nummatches = 0;
                            if (target[nummatches] == newscore2)
                                nummatches++;
                        }
                        else
                            nummatches = 0;
                    }
                }
                else
                {
                    newscore1 = score;
                    _recipes.Add(newscore1);

                    if (target[nummatches] == newscore1)
                        nummatches++;
                    else
                        nummatches = 0;
                }

                if (nummatches == numdigits)
                    break;

                int elf1idx = (_elf1idx + 1 + _recipes[_elf1idx]) % _recipes.Count;
                int elf2idx = (_elf2idx + 1 + _recipes[_elf2idx]) % _recipes.Count;

                _elf1idx = elf1idx;
                _elf2idx = elf2idx;
            }

            Console.WriteLine("Part 2:  Number of recipes to left of target = {0}", _recipes.Count - targetnum.ToString().Length);
        }

        private bool CheckForRecipe(int target)
        {
            int count = _recipes.Count;
            int numdigits = target.ToString().Length;

            if (count < numdigits)
                return false;

            int check = 0;
            int multiplier = 1;
            int lastidx = count - 1;
            int firstidx = count - numdigits;

            for (int i = lastidx; i >= firstidx; i--)
            {
                check += _recipes[i] * multiplier;
                multiplier *= 10;
            }

            return (check == target);
        }

        internal void PrintScores()
        {
            for (int i = 0; i < _recipes.Count; i++)
            {
                if (i == _elf1idx)
                    Console.Write("({0}) ", _recipes[i]);
                else if (i == _elf2idx)
                    Console.Write("[{0}] ", _recipes[i]);
                else
                    Console.Write(" {0}  ", _recipes[i]);
            }
            Console.WriteLine();
        }
        List<int> _recipes;
        int _elf1idx;
        int _elf2idx;
    }
}
