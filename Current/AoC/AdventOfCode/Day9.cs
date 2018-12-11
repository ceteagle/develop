using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class Day9
    {
        public Day9()
        {

        }

        public void Run()
        {
            // 438 players; last marble is worth 71626 points
            int numberOfPlayers = 438;
            int lastMarbleWorth = 71626*100;

            Dictionary<int, int> playerscores = new Dictionary<int, int>();
            List<int> marbles = new List<int>();
            bool winner = false;

            int currentMarble = 0;
            int currentPlayer = 1;
            int currentIndex = 0;
            int idxplus1 = 0;
            int idxplus2 = 0;

            marbles.Add(currentMarble);

            while(!winner)
            {
                if (currentPlayer % (numberOfPlayers+1) == 0)
                    currentPlayer = 1;

                idxplus1 = currentIndex + 1;
                if (idxplus1 == marbles.Count())
                {
                    idxplus1 = 0;
                    idxplus2 = 1;
                }
                else
                {
                    idxplus2 = currentIndex + 2;
                }

                //int idxforinsert = currentIndex + (marbles.Count() >= 2 ? 2 : 1);
                //if (idxforinsert > marbles.Count()+1)
                //    idxforinsert = (idxforinsert - marbles.Count() + 1);

                currentMarble++;
                if (currentMarble % 23 == 0)
                {
                    if (playerscores.ContainsKey(currentPlayer))
                        playerscores[currentPlayer] += currentMarble;
                    else
                        playerscores[currentPlayer] = currentMarble;

                    int sevenless = currentIndex - 7;
                    if( sevenless < 0)
                        sevenless = marbles.Count() + sevenless;
                    playerscores[currentPlayer] += marbles[sevenless];
                    marbles.RemoveAt(sevenless);
                    currentIndex = sevenless;
                    currentPlayer++;
                    continue;
                }

                if (currentMarble == lastMarbleWorth)
                    winner = true;
                if (idxplus2 == 0)
                {
                    marbles.Add(currentMarble);
                    currentIndex = marbles.IndexOf(currentMarble);
                }
                else
                {
                    marbles.Insert(idxplus2, currentMarble);
                    currentIndex = idxplus2;
                }
          
                
                //Console.WriteLine("Player {0} placed marble {1}", currentPlayer, currentMarble);
                currentPlayer++;
            }

            int highscore = 0;
            int winningplayer = 0;

            foreach (var score in playerscores)
            {
                Console.WriteLine("Player {0} score {1}", score.Key, score.Value);
                if( score.Value > highscore)
                {
                    highscore = score.Value;
                    winningplayer = score.Key;
                }
            }

            Console.WriteLine("Player {0} had high score {1}", winningplayer, highscore);
        }
    }
}
