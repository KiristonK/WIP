﻿using System;
using System.Collections.Generic;
using System.Text;

namespace PatternStrategy
{
    internal class PetrolMove : IMovable
    {
        public void Move()
        {
            Console.WriteLine("Petrol moving.");
        }
    }

    internal class ElectroMove : IMovable
    {
        public void Move()
        {
            Console.WriteLine("Electro moving.");
        }
    }

    internal class Hybrid : IMovable
    {
        public void Move()
        {
            Console.WriteLine("Hybrid car.");
        }
    }
    class Car
    {
        public  IMovable Movable { get; set; }
        protected int _passengers;
        protected string _model;

        public Car(int passengers, string model, IMovable mov)
        {
            _passengers = passengers;
            _model = model;
            Movable = mov;
        }

        public void Move()
        {
            Movable.Move();
        }

    }
}
