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
                    _fuelcellgrid[x, y] = new FuelCell() { x = x + 1, y = y + 1, powerlevel = 0 };
                    CalculatePower(x, y);
                }
            }
            //DisplayFuelCell(122, 79);

            //WriteFile();
            //DisplayPowerGrid();
            Find3x3MaxPower();
            FindMaxPowerGrid();
        }

        private void CalculatePower(int x, int y)
        {
            int power = 0;
            int rackid = _fuelcellgrid[x, y].x + 10;
            power = (rackid * _fuelcellgrid[x, y].y + _input) * rackid;

            power /= 100;
            _fuelcellgrid[x, y].powerlevel = (power % 10) - 5;
        }

        private int SumPowerForGrid(int gridx, int gridy, int size)
        {
            int power = 0;

            for (int y = gridy; y < gridy + size; y++)
            {
                for (int x = gridx; x < gridx + size; x++)
                {
                    if (x >= width || y >= height)
                        break;
                    power += _fuelcellgrid[x, y].powerlevel;
                }
            }
            return power;
        }
        private void FindMaxPowerGrid()
        {
            int maxpower = 0;
            int startingx = 0;
            int startingy = 0;
            int finalsize = 0;

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    // Add power 
                    for (int size = 1; size < width-x; size++)
                    {
                        int power = SumPowerForGrid(x, y, size);
                        if (power > maxpower)
                        {
                            maxpower = power;
                            startingx = x + 1;
                            startingy = y + 1;
                            finalsize = size;
                            Console.WriteLine("New max power found at grid point {0},{1} with power {2} and dimension of {3}", startingx, startingy, maxpower, finalsize);
                        }
                    }
                }
                Console.WriteLine("Finished row {0}", y);
            }

            Console.WriteLine("Max Power starts at grid point {0},{1} with power {2} and dimension of {3}", startingx, startingy, maxpower, finalsize);
        }

        private void Find3x3MaxPower()
        {
            int maxpower = 0;
            int startingx = 0;
            int startingy = 0;

            for (int y = 0; y < height - 2; y++)
            {
                for (int x = 0; x < width - 2; x++)
                {
                    int power = _fuelcellgrid[x, y].powerlevel;
                    power += _fuelcellgrid[x + 1, y].powerlevel;
                    power += _fuelcellgrid[x + 2, y].powerlevel;

                    power += _fuelcellgrid[x, y + 1].powerlevel;
                    power += _fuelcellgrid[x + 1, y + 1].powerlevel;
                    power += _fuelcellgrid[x + 2, y + 1].powerlevel;

                    power += _fuelcellgrid[x, y + 2].powerlevel;
                    power += _fuelcellgrid[x + 1, y + 2].powerlevel;
                    power += _fuelcellgrid[x + 2, y + 2].powerlevel;

                    if (power > maxpower)
                    {
                        maxpower = power;
                        startingx = x + 1;
                        startingy = y + 1;
                    }
                }
            }

            Console.WriteLine("Max power 3x3 grid starts at grid point {0},{1} with power {2}", startingx, startingy, maxpower);
        }

        private void DisplayPowerGrid()
        {
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    Console.Write("{0}\t", _fuelcellgrid[x, y].powerlevel);
                }
                Console.WriteLine();
            }
        }

        private void WriteFile()
        {
            string output = string.Empty;

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    output += _fuelcellgrid[x, y].powerlevel.ToString();
                    output += '\t';
                }
                output += '\n';
            }
            System.IO.File.WriteAllText("day11out.txt", output);
        }

        private void DisplayFuelCell(int x, int y)
        {
            Console.WriteLine("Fuel cell at {0},{1}, grid serial number {2}: power level {3}", x, y, _input, _fuelcellgrid[x, y].powerlevel);
        }
    }
}
