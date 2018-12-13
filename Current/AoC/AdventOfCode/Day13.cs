using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    enum turndirection
    {
        left,
        straight,
        right
    }

    public class Cart
    {
        public int xpos { get; set; }
        public int ypos { get; set; }
        public char dir { get; set; }
        public bool crashed { get; set; }

        public void SetTrack(ref char[,] track)
        {
            _track = track;
            _nextTurnDirection = turndirection.left;
            crashed = false;
        }

        public void UpdatePos()
        {
            int newx = xpos;
            int newy = ypos;

            determineNextPos();
        }

        public void PrintCart()
        {
            Console.WriteLine("Cart at {0} {1} heading {2}", xpos, ypos, dir);
        }
        internal void determineNextPos()
        {
            char currpos = _track[xpos, ypos];

            if (currpos == '-')
            {
                if (dir == '>')
                    xpos++;
                else if (dir == '<')
                    xpos--;
            }
            else if (currpos == '+')
            {
                if(_nextTurnDirection == turndirection.left)
                {
                    if(dir == '>')
                    {
                        ypos--;
                        dir = '^';
                    }
                    else if(dir == '<')
                    {
                        ypos++;
                        dir = 'v';
                    }
                    else if(dir == '^')
                    {
                        xpos--;
                        dir = '<';
                    }
                    else if( dir == 'v')
                    {
                        xpos++;
                        dir = '>';
                    }
                    _nextTurnDirection = turndirection.straight;
                }
                else if( _nextTurnDirection == turndirection.straight)
                {
                    if (dir == '>')
                    {
                        xpos++;
                    }
                    else if (dir == '<')
                    {
                        xpos--;
                    }
                    else if (dir == '^')
                    {
                        ypos--;
                    }
                    else if (dir == 'v')
                    {
                        ypos++;
                    }
                    _nextTurnDirection = turndirection.right;
                }
                else if(_nextTurnDirection == turndirection.right)
                {
                    if (dir == '>')
                    {
                        ypos++;
                        dir = 'v';
                    }
                    else if (dir == '<')
                    {
                        ypos--;
                        dir = '^';
                    }
                    else if (dir == '^')
                    {
                        xpos++;
                        dir = '>';
                    }
                    else if (dir == 'v')
                    {
                        xpos--;
                        dir = '<';
                    }
                    _nextTurnDirection = turndirection.left;
                }
            }
            else if (currpos == '|')
            {
                if (dir == '^')
                    ypos--;
                else if (dir == 'v')
                    ypos++;
            }
            else if (currpos == '/')
            {
                if (dir == '^')
                {
                    xpos++;
                    dir = '>';
                }
                else if (dir == 'v')
                {
                    xpos--;
                    dir = '<';
                }
                else if (dir == '<')
                {
                    ypos++;
                    dir = 'v';
                }
                else if (dir == '>')
                {
                    ypos--;
                    dir = '^';
                }
            }
            else if (currpos == '\\')
            {
                if (dir == '^')
                {
                    xpos--;
                    dir = '<';
                }
                else if (dir == 'v')
                {
                    xpos++;
                    dir = '>';
                }
                else if (dir == '>')
                {
                    ypos++;
                    dir = 'v';
                }
                else if (dir == '<')
                {
                    ypos--;
                    dir = '^';
                }
            }
            
        }
        private turndirection _nextTurnDirection;
        private char[,] _track;
    }
    class Day13
    {
        public Day13()
        {
            carts = new List<Cart>();
            _ticks = 0;
        }

        public void Run()
        {
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day13.txt");

            _width = lines[0].Length;
            _height = lines.Length;
            tracks = new char[_width, _height];
            drawable = new char[_width, _height];

            int x = 0;
            int y = 0;

            foreach (var line in lines)
            {
                x = 0;
                foreach (char c in line)
                {
                    if (c == 'v' || c == '^')
                    {
                        carts.Add(new Cart() { xpos = x, ypos = y, dir = c });
                        tracks[x, y] = '|';
                    }
                    else if (c == '<' || c == '>')
                    {
                        carts.Add(new Cart() { xpos = x, ypos = y, dir = c });
                        tracks[x, y] = '-';
                    }
                    else
                        tracks[x, y] = c;

                    drawable[x, y] = tracks[x, y];
                    x++;
                }
                y++;
            }

            foreach (var cart in carts)
            {
                cart.SetTrack(ref tracks);
            }
            DrawTracks();
            Console.ReadKey();
            //CartInfo();

            bool loop = true;
            while (!Collisions())
            {
                OrderCarts();
                if (carts.Count == 1)
                    break;
                foreach (var cart in carts)
                {
                    if (cart.crashed)
                        continue;

                    cart.UpdatePos();
                    if (Collisions())
                    {
                        
                        
                    }
                    if (carts.Count == 1)
                    {
                        loop = false;
                        break;
                    }
                    //cart.PrintCart();
                }
                //DrawTracks();
                //Console.ReadKey();
                //Console.WriteLine();
                _ticks++;
                if (!loop)
                    break;
            }
            Console.WriteLine("Last cart running:");
            CartInfo();
            Console.WriteLine("Ticks = {0}", _ticks);
        }

        internal bool Collisions()
        {
            for (int i = 0; i < carts.Count; i++)
            {
                if (carts[i].crashed)
                    continue;
                for (int j = i+1; j < carts.Count; j++) 
                {
                    if (carts[i].xpos == carts[j].xpos && carts[i].ypos == carts[j].ypos)
                    {
                        drawable[carts[i].xpos, carts[i].ypos] = 'X';
                        //DrawTracks();
                        drawable[carts[i].xpos, carts[i].ypos] = tracks[carts[i].xpos, carts[i].ypos];
                        Console.WriteLine("***COLLISION***");
                        carts[i].PrintCart();
                        carts[j].PrintCart();
                        carts[i].crashed = true;
                        carts[j].crashed = true;
                        return true;
                    }
                }
            }
            
            return false;
        }

        internal void OrderCarts()
        {
            List<Cart> orderedcarts = new List<Cart>();
            foreach (var cart in carts)
            {
                if (cart.crashed)
                    continue;

                bool inserted = false;
                foreach (var c in orderedcarts)
                {
                    if (cart.ypos < c.ypos)
                    {
                        orderedcarts.Insert(orderedcarts.IndexOf(c), cart);
                        inserted = true;
                        break;
                    }
                    else if( cart.ypos == c.ypos)
                    {
                        if(cart.xpos < c.xpos)
                        {
                            orderedcarts.Insert(orderedcarts.IndexOf(c), cart);
                            inserted = true;
                            break;
                        }
                    }
                }
                if(!inserted)
                    orderedcarts.Add(cart);
            }
            carts = orderedcarts;
        }
        internal void DrawTracks()
        {
            Console.Clear();

            for (int y = 0; y < _height; y++)
            {
                for (int x = 0; x < _width; x++)
                {
                    if (drawable[x, y] == 'X')
                        continue;
                    drawable[x, y] = tracks[x, y];
                }
            }
            foreach (var cart in carts)
            {
                if (cart.crashed)
                    continue;
                
                if(drawable[cart.xpos, cart.ypos] != 'X')
                    drawable[cart.xpos, cart.ypos] = cart.dir;
            }
            for (int y = 0; y < _height; y++)
            {
                for (int x = 0; x < _width; x++)
                {
                    if(drawable[x,y] == '>' || drawable[x, y] == '<' || drawable[x, y] == '^' || drawable[x, y] == 'v')
                        Console.ForegroundColor = ConsoleColor.Green;
                    else if(drawable[x,y] == 'X')
                        Console.ForegroundColor = ConsoleColor.Red;
                    else
                        Console.ResetColor();
                    Console.Write(drawable[x, y]);
                }
                Console.WriteLine();
            }
        }

        internal void CartInfo()
        {
            foreach (var cart in carts)
            {
                if (cart.crashed)
                    continue;
                Console.WriteLine("Cart at {0},{1} heading {2}", cart.xpos, cart.ypos, cart.dir);
            }
        }
        char[,] tracks;
        int _width;
        int _height;
        List<Cart> carts;
        char[,] drawable;
        int _ticks;
    }


}
