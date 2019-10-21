using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Threading;

namespace CSharpLessons
{
    class Student : Person
    {
        public static bool Terminate { get; private set; }
        private Point _positionPoint  = new Point(0,20);
        private int _keyPressed;
        private string student =
@"

      ////\\\\
      |      |
     @  O  O  @
      |  ~   |         \__
       \ -- /          |\ |
     ___|  |___        | \|
    /          \      /|__|
   /            \    / /
  /  /| .  . |\  \  / /
 /  / |      | \  \/ /
<  <  |      |  \   /
 \  \ |  .   |   \_/
  \  \|______|
    \_|______|
      |      |
      |  |   |
      |  |   |
      |__|___|
      |  |  |
      (  (  |
      |  |  |
      |  |  |
     _|  |  |
 cccC_Cccc___)
";
        public void Life()
        {
            while (true)
            {
                Console.SetCursorPosition(0, 0);
                Console.Clear();
                Console.Write(Health);
                Console.CursorLeft = 10;
                Console.WriteLine(@"G - Grab; W -  Move forward, S - Move backward");
                Console.SetCursorPosition(_positionPoint.X, _positionPoint.Y);
                Console.WriteLine(student);
                switch (_keyPressed)
                {
                    case 'G':
                    case 'g':
                        Grab(@"Cup");
                        break;
                    case 'W':
                    case 'w':
                        Move(true);
                        _positionPoint.X++;
                        break;
                    case 'S':
                    case 's':
                        Move(false); 
                        _positionPoint.X= _positionPoint.X >= 0 ? _positionPoint.X-- : _positionPoint.X = 0;
                        break;
                    default:
                        Idle();
                        break;
                }
            }
        }

        public void KeyListener()
        {
            _keyPressed = Console.Read();
            if (_keyPressed == 27)
                Terminate = true;
        }
    }
}
