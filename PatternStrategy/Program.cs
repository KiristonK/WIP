using System;

namespace PatternStrategy
{
    static class Program
    {
        static void Main(string[] args)
        {
            Car car = new Car(4, "BMW", new ElectricMove());
            Car car1 = new Car(4, "BMW", new PetrolMove());
            
            car.Move();
            car1.Move();

            car1.Movable = new Hybrid();

            car1.Move();

            car.ShowInfo();
            car1.ShowInfo();

            // Console.WriteLine("Hello World!");
        }
    }
}
