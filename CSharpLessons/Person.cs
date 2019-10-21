using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Text;

namespace CSharpLessons
{
    abstract class Person
    {
        protected uint EyeCount { get; } = 2;
        protected uint ArmCount { get; } = 2;
        protected uint LegCount { get; } = 2;
        protected uint Health { get; } = 100;

       public string Idle()
       {
           return @"Doing nothing.";
       }

       public string Move(bool forward)
       {
           return forward ? @"Moving forward." : @"Moving backward";
       }

       public string Grab(string Object)
       {
           return @"Grabbed " + Object + ".";
       }
    }
}
