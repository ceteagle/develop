using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    public class FuelCell
    {
        public int x { get; set; }
        public int y { get; set; }
        public int powerlevel { get; set; }
    }

    class Day11
    {
        public Day11()
        {
            width = 300;
            height = 300;
            _fuelcellgrid = new FuelCell[width, height];
        }

        public int _input = 5235;
        public int width { get; set; }
        public int height { get; set; }
        public FuelCell[,] _fuelcellgrid;

        public void Run()
        {
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    _fuelcellgrid[x, y] = new FuelCell() { x = x, y = y, powerlevel = 0 };
                    CalculatePower(x, y);
                }
            }
            DisplayPowerGrid();
        }

        private void CalculatePower(int x, int y)
        {
            int power = 0;
            int rackid = _fuelcellgrid[x, y].x + 10;
            power = (rackid * y + _input) * rackid;

            while (power >= 100)
                power /= 10;
            _fuelcellgrid[x, y].powerlevel = power % 10;
        }

        private void DisplayPowerGrid()
        {
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    Console.Write("{0} ", _fuelcellgrid[x, y].powerlevel);
                }
                Console.WriteLine();
            }
        }
    }
}
