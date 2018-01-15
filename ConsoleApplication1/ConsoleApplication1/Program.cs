using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {

            long time;
            time = 13134104216;
            DateTime dateTimeVar = new DateTime(1601, 1, 1).AddSeconds(time);
            Console.WriteLine(dateTimeVar);
            Console.ReadKey();

        }
    }
}
