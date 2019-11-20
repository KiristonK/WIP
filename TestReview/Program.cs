using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestReview
{
    static class Program
    {
        private static void Main()
        {
            var b = (int?) null;

            Console.WriteLine(b);

            var intList = new List<int>{1,2,3,1,5,2,6,5,8,3,8,9,4,8,3,9,3,9,2,68};
            intList.Sort();
            foreach (var item in intList.Distinct())
            {
                Console.WriteLine(item);
            }

            var input = Console.ReadLine();
            var dict = CountLetter(input?.Replace(" ", ""));

            foreach (var item in dict)
            {
                Console.WriteLine($"Letter: {item.Key} Times: {item.Value}");
            }

            Console.ReadLine();
        }

        private static Dictionary<char, int> CountLetter(string input)
        {
            var letters = new Dictionary<char, int>();
            foreach (var letter in input)
            {
                if (!letters.ContainsKey(letter))
                {
                    letters.Add(letter,1);
                }
                else
                {
                    letters[letter]++;
                }
            }
            return letters;
        }
    }
}
