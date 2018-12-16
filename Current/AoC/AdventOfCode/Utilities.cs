using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    namespace Utilities
    {
        public class Cell
        {
            public Cell()
            {
                X = 0;
                Y = 0;
            }
            public Cell(Cell cin)
            {
                X = cin.X;
                Y = cin.Y;
            }
            public int X { get; set; }
            public int Y { get; set; }
        }

        public class BFS
        {
            public int sc { get; set; }
            public int sr { get; set; }

            public int ec { get; set; }
            public int er { get; set; }

            public int C { get; set; }
            public int R { get; set; }

            public UnitType Type { get; set; }

            public BFS(char[,] map, int startx, int starty, int width, int height)
            {
                m = map;
                sc = startx;
                sr = starty;

                C = width;
                R = height;

                cq = new Queue<int>();
                rq = new Queue<int>();

                visited = new bool[C, R];
                prev = new Cell[C, R];

                //dc = new int[4] { 0, 0, +1, -1 };
                //dr = new int[4] { -1, +1, 0, 0 };
                dc = new int[4] { 0, -1, +1, 0 };
                dr = new int[4] { -1, 0, 0, +1 };

                Reset();
            }

            internal void Reset()
            {
                for (int r = 0; r < R; r++)
                {
                    for (int c = 0; c < C; c++)
                    {
                        prev[c, r] = null;
                        visited[c, r] = false;
                    }
                }
                _reachedEnd = false;
                _moveCount = 0;
                _nodesLeftInLayer = 1;
                _nodeInNextLayer = 0;
                cq.Clear();
                rq.Clear();
            }

            public int Solve()
            {
                cq.Enqueue(sc);
                rq.Enqueue(sr);
                visited[sc, sr] = true;
                while (rq.Count > 0)
                {
                    var c = cq.Dequeue();
                    var r = rq.Dequeue();
                    if (c == ec && r == er)
                    {
                        _reachedEnd = true;
                        break;
                    }
                    ExploreNeighbors(c, r);
                    _nodesLeftInLayer--;
                    if (_nodesLeftInLayer == 0)
                    {
                        _nodesLeftInLayer = _nodeInNextLayer;
                        _nodeInNextLayer = 0;
                        _moveCount++;
                    }
                }
                if (_reachedEnd)
                    return _moveCount;
                return -1;
            }

            public List<Cell> Path(int c, int r)
            {
                List<Cell> path = new List<Cell>();

                ec = c;
                er = r;

                Reset();
                Solve();

                Cell at = new Cell() { X = c, Y = r };

                for (; at != null; at = prev[at.X, at.Y])
                {
                    path.Add(at);
                }
                path.Reverse();
                return path;
            }
            public void ExploreNeighbors(int c, int r)
            {
                for (int i = 0; i < 4; i++)
                {
                    var cc = c + dc[i];
                    var rr = r + dr[i];

                    if (cc < 0 || rr < 0) continue;
                    if (cc >= C || rr >= R) continue;

                    if (visited[cc, rr]) continue;
                    if (m[cc, rr] != '.' && !(cc == ec && rr == er)) continue;

                    cq.Enqueue(cc);
                    rq.Enqueue(rr);
                    visited[cc, rr] = true;
                    prev[cc, rr] = new Cell();
                    prev[cc, rr].X = c;
                    prev[cc, rr].Y = r;

                    _nodeInNextLayer++;
                }
            }

            int[] dc;
            int[] dr;

            Queue<int> cq;
            Queue<int> rq;

            bool[,] visited;
            char[,] m;

            Cell[,] prev;

            bool _reachedEnd;
            int _moveCount;
            int _nodesLeftInLayer;
            int _nodeInNextLayer;
        }
        

    }
}
