using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Backup
{
    public class BackupTool
    {
        public int NumberOfDirectoriesCreated { get { return _directoriesCreated.Count; } }
        public int NumberOfFilesCopied { get { return _filesCopied.Count; } }

        public IEnumerable<string> FilesCopied { get { return _filesCopied; } }
        public IEnumerable<string> DirectoriesCreated { get { return _directoriesCreated; } }

        private List<string> _filesCopied;
        private List<string> _directoriesCreated;

        public BackupTool()
        {
            _filesCopied = new List<string>();
            _directoriesCreated = new List<string>();
        }

        public void RecursiveCopy(string sourceDirectory, string targetDirectory)
        {
            foreach (var dir in Directory.GetDirectories(sourceDirectory))
            {
                var dirName = Path.GetFileName(dir);
                var target = Path.Combine(targetDirectory, dirName);
                if (!Directory.Exists(target))
                {
                    Directory.CreateDirectory(target);
                    _directoriesCreated.Add(target);
                    RecursiveCopy(dir, target);
                }
                foreach (var file in Directory.GetFiles(dir))
                {
                    var fileName = Path.GetFileName(file);
                    var targetFile = Path.Combine(target, fileName);
                    if (!File.Exists(targetFile))
                    {
                        File.Copy(file, targetFile);
                        _filesCopied.Add(targetFile);
                    }
                }
            }
        }

        public void Report()
        {
            Console.WriteLine("Number of directories created {0}", NumberOfDirectoriesCreated);
            Console.WriteLine("Number of files copied        {0}", NumberOfFilesCopied);

            Console.WriteLine("\n*** Directories created ***");
            foreach (var dir in _directoriesCreated)
            {
                Console.WriteLine(dir);
            }

            Console.WriteLine("\n*** Files copied ***");
            foreach (var file in _filesCopied)
            {
                Console.WriteLine(file);
            }

            Console.WriteLine("\n\n=== END OF PROGRAM ===");
        }
    }
}
