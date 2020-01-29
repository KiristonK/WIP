using System;
using System.Threading;
using System.Threading.Tasks;

namespace CSharpLessons
{
    class Program
    {
        static void Main()
        {
            for (var i = 0; i < 320; i+=5)
            {
                var i1 = i;
                Task.Run(() => DrawMatrix(i1));
            }

            while (true)
            {
                
            }
        }

        static async void DrawMatrix(int pos)
        {
            var rand = new Random();
            await Task.Run(() =>
            {
                bool down = true;
                while (true)
                {
                    Console.CursorLeft = pos;
                    if (down)
                        Console.CursorTop++;
                    else
                        Console.CursorTop--;
                    Console.WriteLine(rand.Next(0, 2));
                    if (Console.CursorTop == 25)
                        down = false;
                    if (Console.CursorTop == 10)
                        down = true;
                    Thread.Sleep(200);
                }
            });
        }
    }
}
