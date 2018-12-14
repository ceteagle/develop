using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    public class Elf
    {
        public int recipescore { get; set; }
        public int scoreidx { get; set; }
    }


    class Day14
    {
        public Day14()
        {
            _recipes = new List<int>() { 3, 7 };

            _elf1 = new Elf();
            _elf2 = new Elf();

            _elf1.recipescore = 3;
            _elf1.scoreidx = 0;

            _elf2.recipescore = 7;
            _elf2.scoreidx = 1;

        }

        public void Run()
        {
            for (int i = 0; i < 16; i++)
            {
                PrintScores();
                int score = _recipes[_elf1.scoreidx] + _recipes[_elf2.scoreidx];
                int newscore1 = 0;
                int newscore2 = 0;
                if(score>9)
                {
                    newscore1 = score / 10;
                    newscore2 = score % 10;
                }
                else
                {
                    newscore1 = score;
                    newscore2 = 0;
                }

                _recipes.Add(newscore1);
                _recipes.Add(newscore2);

                int elf1idx = _elf1.scoreidx + 1 + _recipes[_elf1.scoreidx];
                int elf2idx = _elf2.scoreidx + 1 + _recipes[_elf2.scoreidx];

                while(elf1idx >= _recipes.Count)
                {
                    elf1idx = elf1idx - _recipes.Count;
                }

                while (elf2idx >= _recipes.Count)
                {
                    elf2idx = elf2idx - _recipes.Count;
                }

                _elf1.scoreidx = elf1idx;
                _elf2.scoreidx = elf2idx;

                
            }
            PrintScores();
        }

        internal void PrintScores()
        {
            for (int i = 0; i < _recipes.Count; i++)
            {
                if( i == _elf1.scoreidx)
                    Console.Write("({0}) ", _recipes[i]);
                else if( i == _elf2.scoreidx)
                    Console.Write("[{0}] ", _recipes[i]);
                else
                    Console.Write(" {0}  ", _recipes[i]);
            }
            Console.WriteLine();
        }
        List<int> _recipes;
        Elf _elf1;
        Elf _elf2;
    }
}
