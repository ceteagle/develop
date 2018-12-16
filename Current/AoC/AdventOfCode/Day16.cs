using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace AdventOfCode
{
    static class Instructions
    {
        static public void addr(int a, int b, int c, int[] r) { r[c] = r[a] + r[b]; }
        static public void addi(int a, int b, int c, int[] r) { r[c] = r[a] + b; }
        static public void mulr(int a, int b, int c, int[] r) { r[c] = r[a] * r[b]; }
        static public void muli(int a, int b, int c, int[] r) { r[c] = r[a] * b; }
        static public void banr(int a, int b, int c, int[] r) { r[c] = r[a] & r[b]; }
        static public void bani(int a, int b, int c, int[] r) { r[c] = r[a] & b; }
        static public void borr(int a, int b, int c, int[] r) { r[c] = r[a] | r[b]; }
        static public void bori(int a, int b, int c, int[] r) { r[c] = r[a] | b; }
        static public void setr(int a, int b, int c, int[] r) { r[c] = r[a]; }
        static public void seti(int a, int b, int c, int[] r) { r[c] = a; }
        static public void gtir(int a, int b, int c, int[] r) { r[c] = a > r[b] ? 1 : 0; }
        static public void gtri(int a, int b, int c, int[] r) { r[c] = r[a] > b ? 1 : 0; }
        static public void gtrr(int a, int b, int c, int[] r) { r[c] = r[a] > r[b] ? 1 : 0; }
        static public void eqir(int a, int b, int c, int[] r) { r[c] = a == r[b] ? 1 : 0; }
        static public void eqri(int a, int b, int c, int[] r) { r[c] = r[a] == b ? 1 : 0; }
        static public void eqrr(int a, int b, int c, int[] r) { r[c] = r[a] == r[b] ? 1 : 0; }
    }

    public enum Opcodes
    {
        ADDR,
        ADDI,
        MULR,
        MULI,
        BANR,
        BANI,
        BORR,
        BORI,
        SETR,
        SETI,
        GTIR,
        GTRI,
        GTRR,
        EQIR,
        EQRI,
        EQRR
    }

    class Day16
    {
        private int[] registers;
        public int DecodedInstructions { get; set; }
        private Dictionary<int, List<Opcodes>> _possibleOpcodeMap;
        public Day16()
        {
            registers = new int[4] { 0, 0, 0, 0 };
            DecodedInstructions = 0;
            _possibleOpcodeMap = new Dictionary<int, List<Opcodes>>();
        }

        public void Part1()
        {
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day16.txt");

            int[] registersbefore = new int[4] { 0, 0, 0, 0 };
            int[] registersafter = new int[4] { 0, 0, 0, 0 };
            int[] instruction = new int[4] { 0, 0, 0, 0 };

            int ctr = 0;
            foreach (var line in lines)
            {
                //Before: [2, 3, 2, 2]
                //0 3 3 0
                //After:  [0, 3, 2, 2]
                if (line.Count() == 0)
                    continue;
                if (line.StartsWith("Before"))
                {
                    var matches = Regex.Matches(line, @"[(\d*)]");
                    int idx = 0;
                    foreach (var match in matches)
                    {
                        registersbefore[idx++] = Int32.Parse(match.ToString());
                    }
                }
                else if (line.StartsWith("After"))
                {
                    var matches = Regex.Matches(line, @"[(\d*)]");
                    int idx = 0;
                    foreach (var match in matches)
                    {
                        registersafter[idx++] = Int32.Parse(match.ToString());
                    }
                }
                else
                {
                    string[] numbers = Regex.Split(line, @"\D+");
                    int idx = 0;
                    foreach (var number in numbers)
                    {
                        instruction[idx++] = Int32.Parse(number);
                    }
                }
                ctr++;
                if (ctr % 3 == 0)
                {
                    var insts = FindInstruction(registersbefore, registersafter, instruction);
                    List<Opcodes> intersect = new List<Opcodes>();
                    if (!_possibleOpcodeMap.ContainsKey(instruction[0]))
                    {
                        _possibleOpcodeMap[instruction[0]] = new List<Opcodes>();
                        _possibleOpcodeMap[instruction[0]] = insts;
                    }
                    else
                    {
                        foreach (var inst in insts)
                        {
                            if (_possibleOpcodeMap[instruction[0]].Contains(inst))
                                continue;
                            _possibleOpcodeMap[instruction[0]].Add(inst);
                        }
                        
                    }

                    if (insts.Count >= 3)
                        DecodedInstructions++;
                }
            }

            Console.WriteLine("Part 1 Answer: #Decoded Instructions = {0}", DecodedInstructions);
        }

        private List<Opcodes> FindInstruction(int[] registersbefore, int[] registersafter, int[] instruction)
        {
            int opcode = instruction[0];
            int A = instruction[1];
            int B = instruction[2];
            int C = instruction[3];

            List<Opcodes> possibleOpcodes = new List<Opcodes>();

            int[] r = new int[4] { 0, 0, 0, 0 };

            registersbefore.CopyTo(r, 0);
            Instructions.addr(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.ADDR);

            registersbefore.CopyTo(r, 0);
            Instructions.addi(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.ADDI);

            registersbefore.CopyTo(r, 0);
            Instructions.mulr(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.MULR);

            registersbefore.CopyTo(r, 0);
            Instructions.muli(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.MULI);

            registersbefore.CopyTo(r, 0);
            Instructions.banr(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.BANR);

            registersbefore.CopyTo(r, 0);
            Instructions.bani(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.BANI);

            registersbefore.CopyTo(r, 0);
            Instructions.borr(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.BORR);

            registersbefore.CopyTo(r, 0);
            Instructions.bori(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.BORI);

            registersbefore.CopyTo(r, 0);
            Instructions.setr(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.SETR);

            registersbefore.CopyTo(r, 0);
            Instructions.seti(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.SETI);

            registersbefore.CopyTo(r, 0);
            Instructions.gtir(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.GTIR);

            registersbefore.CopyTo(r, 0);
            Instructions.gtri(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.GTRI);

            registersbefore.CopyTo(r, 0);
            Instructions.gtrr(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.GTRR);

            registersbefore.CopyTo(r, 0);
            Instructions.eqir(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.EQIR);

            registersbefore.CopyTo(r, 0);
            Instructions.eqri(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.EQRI);

            registersbefore.CopyTo(r, 0);
            Instructions.eqrr(A, B, C, r);
            if (r.SequenceEqual(registersafter)) possibleOpcodes.Add(Opcodes.EQRR);

            return possibleOpcodes;
        }

        public void Part2()
        {
            int[] instruction = new int[4] { 0, 0, 0, 0 };

            Part1();

            //PrintOpcodeMap();

            ReduceMap();

            //Console.WriteLine("After reductions");
            //PrintOpcodeMap();

            // Read part 2 from file
            //
            string[] lines = System.IO.File.ReadAllLines(@"..\..\day16part2.txt");
            foreach (var line in lines)
            {
                string[] numbers = Regex.Split(line, @"\D+");
                int idx = 0;
                foreach (var number in numbers)
                {
                    instruction[idx++] = Int32.Parse(number);
                }

                if (_possibleOpcodeMap.ContainsKey(instruction[0]) == false)
                {
                    Console.WriteLine("Unknown opcode {0}", instruction[0]);
                    continue;
                }

                //Console.WriteLine("{0} {1} {2} {3}", _possibleOpcodeMap[instruction[0]][0].ToString(), instruction[1], instruction[2], instruction[3]);

                switch (_possibleOpcodeMap[instruction[0]][0])
                {
                    case Opcodes.ADDI:
                        Instructions.addi(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.ADDR:
                        Instructions.addr(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.MULR:
                        Instructions.mulr(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.MULI:
                        Instructions.muli(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.BANR:
                        Instructions.banr(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.BANI:
                        Instructions.bani(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.BORR:
                        Instructions.borr(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.BORI:
                        Instructions.bori(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.SETR:
                        Instructions.setr(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.SETI:
                        Instructions.seti(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.GTIR:
                        Instructions.gtir(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.GTRI:
                        Instructions.gtri(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.GTRR:
                        Instructions.gtrr(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.EQIR:
                        Instructions.eqir(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.EQRI:
                        Instructions.eqri(instruction[1], instruction[2], instruction[3], registers);
                        break;
                    case Opcodes.EQRR:
                        Instructions.eqrr(instruction[1], instruction[2], instruction[3], registers);
                        break;
                }

            }

            for (int i = 0; i < 4; i++)
            {
                Console.WriteLine("Register[{0}] = {1}", i, registers[i]);
            }
            Console.WriteLine("\nPart 2 Answer: Register[0] = {0}", registers[0]);

        }

        private void ReduceMap()
        {
            bool works = true;
            Dictionary<int, List<Opcodes>> rmap = new Dictionary<int, List<Opcodes>>();

            bool reduction = true;
            while (reduction)
            {
                reduction = false;
                List<Opcodes> singleOpcodes = new List<Opcodes>();
                foreach (var kvpair in _possibleOpcodeMap)
                {
                    if (kvpair.Value.Count == 1)
                    {
                        singleOpcodes.Add(kvpair.Value[0]);
                    }
                }

                foreach (var opcode in singleOpcodes)
                {
                    foreach (var kvpair in _possibleOpcodeMap)
                    {
                        if (kvpair.Value.Count == 1)
                            continue;

                        if (kvpair.Value.Contains(opcode))
                        {
                            kvpair.Value.Remove(opcode);
                            reduction = true;
                        }
                    }
                }
            }
        }

        private void PrintOpcodeMap()
        {
            foreach (var pair in _possibleOpcodeMap)
            {
                Console.Write("{0} => ", pair.Key);
                foreach (var opcode in pair.Value)
                {
                    Console.Write("{0} ", opcode.ToString());
                }
                Console.WriteLine();
            }
        }
    }
}
