using static System.Console;
namespace Lesson1
{
    class Program
    {
        static void Main(string[] args)
        {
            //while (true)
            //{
            //    WriteLine("Podaj imie :");
            //    var name = ReadLine();
            //    WriteLine("Podaj nazwisko :");
            //    var surname = ReadLine();
            //    Write("Podaj swoj wiek : ");
            //    int age = int.Parse(ReadLine());
            //    if (age > 0 && age < 101) {
            //        for (int i = 0; i < (age % 2 == 0 ? 2 : 1); i++)
            //            WriteLine($"{name} {surname}, twoj wiek : {age}");
            //        break;
            //    }
            //    WriteLine("Wiek musi byc podany w zakresie od 1 do 100");
            //    System.Threading.Thread.Sleep(1000);
            //    Clear();
            //}

            var bmw = new car("BMW");
            bmw.Drive();
            ReadKey();
        }
    }

    class car
    {
        private readonly int _wheels;
        private string model = "Audi";
        public car(string model)
        {
            _wheels = 4;
            model = this.model;
        }

        public car()
        { }
        public void Drive()
        {
            WriteLine($"{model} with {_wheels} wheels moves");
        }
    }
}