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

        Point _usedPos = new Point(0, 0);
        const int StdOutputHandle = -11;
        const uint EnableVirtualTerminalProcessing = 4;

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr GetStdHandle(int nStdHandle);

        [DllImport("kernel32.dll")]
        static extern bool GetConsoleMode(IntPtr hConsoleHandle, out uint lpMode);

        [DllImport("kernel32.dll")]
        static extern bool SetConsoleMode(IntPtr hConsoleHandle, uint dwMode);

        private char[,] _field =
        {
            {'T', 'H', 'O', 'Q', 'K', 'O', 'H', 'T'},
            {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
            {'T', 'H', 'O', 'Q', 'K', 'O', 'H', 'T'}
        };

        private int _cursorLeft;
        private int _cursorTop;

        public void UsedPos()
        {
            _cursorLeft = _usedPos.X;
            _cursorTop = _usedPos.Y;
            var input = Console.ReadKey();
            switch (input.Key)
            {
                case ConsoleKey.RightArrow:
                    if (_usedPos.X != 7) _usedPos.X++;
                    else _usedPos.X = 0;
                    break;
                case ConsoleKey.LeftArrow:
                    if (_usedPos.X != 0) _usedPos.X--;
                    else _usedPos.X = 7;
                    break;
                case ConsoleKey.UpArrow:
                    if (_usedPos.Y != 0) _usedPos.Y--;
                    else _usedPos.Y = 7;
                    break;
                case ConsoleKey.DownArrow:
                    if (_usedPos.Y != 7) _usedPos.Y++;
                    else _usedPos.Y = 0;
                    break;
                case ConsoleKey.Escape:
                    Environment.Exit(0);
                    break;
                case ConsoleKey.Enter:
                    ChessMove(input, _field[_usedPos.Y,_usedPos.X]);
                    break;
            }
        }

        private void ChessMove(in ConsoleKeyInfo input, char chess)
        {
            switch (input.Key)
            {
                case ConsoleKey.UpArrow:

                    break;
                case ConsoleKey.DownArrow:

                    break;
                case ConsoleKey.RightArrow:

                    break;
                case ConsoleKey.LeftArrow:

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
                if (_cursorLeft != _usedPos.X || _cursorTop != _usedPos.Y)
                {
                    Console.Clear();
                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            Console.Write((i, j) == (_usedPos.Y, _usedPos.X)
                                ? underline + _field[i, j] + reset + " "
                                : _field[i, j] + " ");
                        }

                        Console.WriteLine();
                    }
                }
            }
        }
    }
}
