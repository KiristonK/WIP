using System;
using System.Threading;
using System.Threading.Tasks;

namespace CSharpLessons
{
    class Program
    {
        static void Main()
        {
            //for (int i = 0; i < Console.WindowWidth; i++)
            //{
            //    var i1 = i;
                Task.Run(() => DrawMatrix(1));
            //}

            while (true)
            {
                
            }
        }

        static async void DrawMatrix(int pos)
        {
            var rand = new Random();
            await Task.Run(() =>
            {
                while (true)
                {
                    Console.CursorTop = pos;
                    Console.WriteLine(rand.Next(0, 2));
                }
            });
        }
    }
}
