using System;
using System.Threading;

namespace Chess
{
    class Program
    {
        static void Main(string[] args)
        {
            Field field = new Field();
            Thread posThread = new Thread(field.FieldDraw);
            posThread.Start();
            while (true)
            {
                field.UsedPos();
               
                Thread.Sleep(30);
            }
        }
    }
}
