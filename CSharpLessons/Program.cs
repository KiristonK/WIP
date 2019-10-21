using System;
using System.Threading;

namespace CSharpLessons
{
    class Program
    {
        static void Main()
        {
            Student student = new Student();
             Thread thread = new Thread(student.KeyListener);
             thread.Start();
             Thread lifeThread = new Thread(student.Life);
             lifeThread.Start();
             if (Student.Terminate)
             {
                 Console.WriteLine("Terminating Processes...");
                 thread.Abort();
                 lifeThread.Abort();
                 Thread.Sleep(2000);
                 Thread.CurrentThread.Abort();
                 return;
             }
        }
    }
}
