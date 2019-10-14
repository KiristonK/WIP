using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ComsoleC_Sharp
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] fruits = { "Apple", "Banana", "Pineapple"};
            string fruit = "AppleBanana";
            Console.WriteLine(fruit.Substring(5));
            Console.WriteLine(fruit.Substring(5, 6));
            int x = int.Parse(Console.ReadLine());
            int y = int.Parse(Console.ReadLine());
            int[,] matrix = new int[x, y];
            
        }
    }
}
