using System;
using System.Collections.Generic;
using System.Drawing;
using System.Net.Mime;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading;
using Microsoft.Win32.SafeHandles;

namespace Chess
{
    class Field
    {
        public Field()
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Console.Write(_field[i, j] + " ");
                }
                Console.WriteLine();
            }
        }
        
        Point usedPos = new Point(0,0);
        const int StdOutputHandle = -11;
        const uint EnableVirtualTerminalProcessing = 4;

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr GetStdHandle(int nStdHandle);

        [DllImport("kernel32.dll")]
        static extern bool GetConsoleMode(IntPtr hConsoleHandle, out uint lpMode);

        [DllImport("kernel32.dll")]
        static extern bool SetConsoleMode(IntPtr hConsoleHandle, uint dwMode);

        private char [,] _field  = 
        {
            { 'T', 'H', 'O', 'Q', 'K', 'O', 'H', 'T'},
            { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
            { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
            { 'T', 'H', 'O', 'Q', 'K', 'O', 'H', 'T'}
        };

        private int _cursorLeft;
        private int _cursorTop;
        public void UsedPos()
        {
            var input = Console.ReadKey();
            switch (input.Key)
            {
                case ConsoleKey.RightArrow:
                    if (usedPos.X != 7) { _cursorLeft = usedPos.X; usedPos.X+=2;} else { _cursorLeft = usedPos.X; usedPos.X = 0;}
                    break;
                case ConsoleKey.LeftArrow:
                    if (usedPos.X != 0) { _cursorLeft = usedPos.X; usedPos.X-=2;} else { _cursorLeft = usedPos.X; usedPos.X = 7;}
                    break;
                case ConsoleKey.UpArrow:
                    if (usedPos.Y != 0) { _cursorTop = usedPos.Y; usedPos.Y-=2;} else { _cursorTop = usedPos.Y; usedPos.Y = 7;}
                    break;
                case ConsoleKey.DownArrow:
                    if (usedPos.Y != 7) { _cursorTop = usedPos.Y; usedPos.Y+=2;} else{ _cursorTop = usedPos.Y; usedPos.Y = 0;}
                    break;
                case ConsoleKey.Escape:
                    Environment.Exit(0);
                    break;
            }
        }

        public void FieldDraw()
        {
            while (true)
            {
                var handle = GetStdHandle(StdOutputHandle);
                GetConsoleMode(handle, out var mode);
                mode |= EnableVirtualTerminalProcessing;
                SetConsoleMode(handle, mode);

                const string underline = "\x1B[4m";
                const string reset = "\x1B[0m";

                Console.SetCursorPosition(usedPos.X, usedPos.Y);
                Console.Write(underline + _field[usedPos.Y, usedPos.X] + reset);
                Console.SetCursorPosition(_cursorLeft, _cursorTop);
                Console.Write(_field[usedPos.Y, usedPos.X]);

                Thread.Sleep(100);
            }
        }
    }
}
