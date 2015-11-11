using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Backup
{
    class Program
    {
        static void Main(string[] args)
        {

            var sourceBaseDirectory = @"\\MYMEDIA\Public\Shared Pictures";
            var targetBaseDirectory = @"\\MEDIABACKUP\Public\Pictures";

            if (!Directory.Exists(targetBaseDirectory))
                Directory.CreateDirectory(targetBaseDirectory);

            BackupTool bt = new BackupTool();
            Console.WriteLine("=== BACKING UP PICTURES ===");
            bt.RecursiveCopy(sourceBaseDirectory, targetBaseDirectory);

            Console.WriteLine("\n=== BACKING UP VIDEOS ===");
            sourceBaseDirectory = @"\\MYMEDIA\Public\Shared Videos";
            targetBaseDirectory = @"\\MEDIABACKUP\Public\Videos";
            bt.RecursiveCopy(sourceBaseDirectory, targetBaseDirectory);

            bt.Report();
        }
    }
}
