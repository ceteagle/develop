using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode
{
    class Node
    {
        public Node()
        {
            metadata = new List<int>();
            children = new List<Node>();
            id = numchildren = nummeta = 0;
        }

        public int KeyValue()
        {
            if (numchildren == 0)
                return MetaSum();

            int key = 0;
            foreach (var idx in metadata)
            {
                if (idx > numchildren)
                    continue;
                key += children.ElementAt(idx-1).KeyValue();
            }
            return key;
        }

        public int MetaSum()
        {
            int sum = 0;
            foreach (var meta in metadata)
            {
                sum += meta;
            }
            return sum;
        }

        public int id;
        public int numchildren;
        public int nummeta;
        public List<int> metadata;
        public List<Node> children;
        
    }

    class Day8
    {
        public Day8()
        {
            nodes = new List<Node>();
        }

        internal Node ProcessHeader(ref string[] data, ref int pos)
        {
            if (pos >= data.Length)
                return null;

            var node = new Node();
            node.numchildren = Int32.Parse(data[pos++]);
            node.nummeta = Int32.Parse(data[pos++]);
            return node;
        }

        internal void ProcessMeta(ref string[] data, ref int pos, ref Node node)
        {
            for (int i = 0; i < node.nummeta; i++)
            {
                node.metadata.Add(Int32.Parse(data[pos++]));
            }
        }

        internal void ProcessArray(ref string[] data, ref int pos, ref Node parent)
        {

            var node = ProcessHeader(ref data, ref pos);

            for (int i = 0; i < node.numchildren; i++)
            {
                ProcessArray(ref data, ref pos, ref node);
            }

            ProcessMeta(ref data, ref pos, ref node);
            
            parent.children.Add(node);
        }

        public void Run()
        {
            //  2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2
            //  A----------------------------------
            //      B---------- - C---------- -
            //                       D---- -

            /*
            A, which has 2 child nodes (B, C) and 3 metadata entries (1, 1, 2).
            B, which has 0 child nodes and 3 metadata entries (10, 11, 12).
            C, which has 1 child node (D) and 1 metadata entry (2).
            D, which has 0 child nodes and 1 metadata entry (99).
            */

            string[] lines = System.IO.File.ReadAllLines(@"..\..\day8.txt");
            //string[] lines = { "2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2" };
            var root = new Node();

            foreach (var line in lines)
            {
                string[] d = line.Split(' ');
                if (d.Length < 2)
                    break;

                int pos = 0;

                root = ProcessHeader(ref d, ref pos);
               
                for (int i = 0; i < root.numchildren; i++)
                {
                    ProcessArray(ref d, ref pos, ref root);
                }

                ProcessMeta(ref d, ref pos, ref root);

            }

            int metaSum = SumMeta(root);
            foreach (var meta in root.metadata)
            {
                metaSum += meta;
            }
            Console.WriteLine("Meta sum is {0}", metaSum);
            Console.WriteLine("Key is {0}", root.KeyValue());
        }

        private int SumMeta(Node node)
        {
            int sum = 0;
            foreach (var child in node.children)
            {
                sum += child.MetaSum();

                sum += SumMeta(child);
            }
            return sum;
        }

        public List<Node> nodes;
    }
}
