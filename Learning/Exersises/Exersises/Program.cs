using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

using static  System.Console;

namespace Exersises
{
    class Program
    {
        static void Main(string[] args)
        {
            //WriteLine("Enter string: ");
            //var str = ReadLine();
            //WriteLine("Result: " + new ReverseProgramming().MysteryFunc(str));

            // WriteLine(new ReverseProgramming().CalculateExponent(long.Parse(ReadLine() ?? throw new InvalidOperationException()),
            //     long.Parse(ReadLine() ?? throw new InvalidOperationException())));

            //WriteLine(new ReverseProgramming().MissingNum(new int[] {7, 2, 3, 6, 5, 9, 1, 4, 8}));
            //foreach (var num in new ReverseProgramming().FindLargest(new double[][]
            //    {new double[] {-34, -54, -74}, new double[] {-32, -2, -65}, new double[] {-54, 7, -43}}))
            //{
            //    Write(num + "\t");
            //}

            //var res = new ReverseProgramming().PalindromeDescendant(11211230);
            //WriteLine(res);
            //var res1 = new ReverseProgramming().IndexOfCapitals("eDaBiT");
            //foreach (var num  in res1)
            //{
            //    WriteLine(num);
            //}
            //WriteLine(new ReverseProgramming().IsStrangePair("",""));

            //var simp = new ReverseProgramming().Simplify("5/7");
            //WriteLine(simp);
            //new ReverseProgramming().ValidateEmail("@email");
            //new ReverseProgramming().AlmostPalindrome("gggggg");
            //new ReverseProgramming().ConvertTime(ReadLine());
            var sol = new Solution();
            Console.WriteLine(sol.solution(18,2));
            Console.WriteLine(sol.WeekdayRobWasBornInDutch(2001,12,2));
            Console.ReadLine();
        }

        public static int[] MultiplyByLength(int[] arr)
        {
            var list =  arr.ToList();
            var len = arr.Length;
            for (int i = 0; i < len; i++)
            {
                arr[i] *= len;
            }
            return arr;
        }

        public static int CountWords(string str)
        {
            return str.Count(x => x == ' ');
        }
    }

    class Solution
    {
        //public int solution(int[] A)
        //{
        //    // write your code in C# 6.0 with .NET 4.5 (Mono)
        //    var min = 1;
        //    while (true)
        //    {
        //        if (A.Any(num => min == num))
        //        {
        //            min++;
        //        }else return min;
        //    }
        //}

        public string WeekdayRobWasBornInDutch(int year, int month, int day) => 
            CultureInfo.GetCultureInfo("nl-NL").DateTimeFormat.GetDayName(new DateTime(year, month, day).DayOfWeek);
        public int solution(int N, int K)
        {
            var res = 0;
            while (N != 1)
            {
                if (N % 2 == 0 && K != 0)
                {
                    N /= 2;
                    K--;
                    res++;
                }
                else
                {
                    N -= 1;
                    res++;
                }
            }
            return res;
        }
    }
    internal class ReverseProgramming
    {
        public string ConvertTime(string time)
        {
            if (time.EndsWith("am"))
                return time.Substring(0, 2) == "12" ? "0:00" : time.Substring(0, 5);
            if (time.EndsWith("pm"))
                return (int.Parse(time.Split(':')[0]) + 12) != 24 ? int.Parse(time.Split(':')[0]) + 12 + ":" + int.Parse(time.Split(':')[1].Substring(0, 2)) : "0:" + int.Parse(time.Split(':')[1].Substring(0, 2));
            return int.Parse(time.Split(':')[0]) > 12 ? int.Parse(time.Split(':')[0]) - 12 + ":" + time.Split(':')[1] + " pm" : time + " am";
        }
        public string MysteryFunc(string str)
        {
            var res = string.Empty;
            for (var i = 0; i < str.Length; i++)
            {
                if (str[i] < '0' || str[i] > '9') continue;
                res += str[i-1];
                WriteLine("("+i+") "+ str[i] + " char: " + str[i-1]);
                for (var j = 0; j < int.Parse(str[i].ToString()); j++)
                    res += str[i - 1];
            }
            Array.Sort(str.ToCharArray());
            return res;
        }

        public static int MysteryFunc(int num)
        {
            var str = num.ToString();
            return int.Parse(str[0].ToString()) * str.Substring(1).Select(x=>int.Parse(x.ToString())).ToArray().Sum();
        }

        public bool AlmostPalindrome(string str)
        {
            if (str.ToCharArray().Take(str.Length).SequenceEqual(str.Reverse().ToArray())) return false;
            for (var i = 0; i < str.Length; i++)
                if (str[i] != str[str.Length - 1 - i])
                {
                    str = str.Remove(str.Length - 1 - i, 1) + str[i];
                    break;
                }
            var strArr = str.ToCharArray();
            Array.Reverse(strArr);
            return str.Equals(new string(strArr));
        }
        public static bool IsValidPhoneNumber(string str)
        {
            return System.Text.RegularExpressions.Regex.IsMatch(str, @"^[(]\d{3}[)]\s\d{3}(-\d{4})$");

        }

        public  bool ValidateEmail(string str) => Regex.Replace(str, @"@.*\..*", string.Empty).Length > 0 && Regex.Replace(str, @"@.*\..*", string.Empty) != str;

        public string Simplify(string str)
        {
            var nums = str.Split('/').Select(int.Parse).ToArray();
            for (var i = 1; i < nums[1]; i++)
            {
                Console.WriteLine(i);
                if (nums[0] % i != 0 && nums[1] % i != 0) continue;
                nums[0] /= i;
                nums[1] /= i;
            }
            Console.WriteLine(nums[0] + "/" + nums[1]);
            return nums[0] + "/" + nums[1];
        }

        public int[] ArrayOfMultiples(int num, int length)
        {
            var res = new int[length];
            for (var i = 1; i < length; i++)
            {
                res[i] = res[i - 1] + num;
            }
            return res;
        }

        public bool IsStrangePair(string str1, string str2) => string.IsNullOrEmpty(str1) ? string.IsNullOrEmpty(str2) :
            (str1.StartsWith(str2.Last().ToString()) &&
             str1.EndsWith(str2.First().ToString()));

        public string HighLow(string str)
        {
            return str.Max() + " " + str.Min();
        }

        public bool PalindromeDescendant(int num)
        {
            var numStr = num.ToString();
            for (var i = 0; i < numStr.Length / 2; i++)
            {
                if (numStr[i] != numStr[numStr.Length - 1 - i])
                {
                    var newParam = string.Empty;
                    for (var j = 0; j < numStr.Length; j += 2)
                    {
                        var secNum = j + 1 >= numStr.Length ? 0 : int.Parse(numStr[j + 1].ToString());
                        newParam += int.Parse(numStr[j].ToString()) + secNum;
                    }
                    return newParam.Length >= 2 && PalindromeDescendant(int.Parse(newParam));
                }
                if (i == (numStr.Length / 2) - 1) return true;
            }
            return false;
        }

        public  bool isBetween(string first, string last, string word)
        {
            var sorted = new string[3] { first, last, word };
            Array.Sort(sorted, StringComparer.InvariantCulture);
            return sorted[1] == word;
        }

        public  double[] CumulativeSum(double[] arr)
        {
            var res = new double[arr.Length];
            for (var i = 0; i < res.Length; i++)
            {
                res[i] = arr[i] + res[i - 1];
            }
            return res;
        }

        public static string GetMiddle(string str)
        {
            return str.Length % 2 == 0 ? str[str.Length / 2].ToString() : str[str.Length / 2].ToString() + str[str.Length / 2 + 1].ToString();
        }

        public int[] IndexOfCapitals(string str)
        {
            var res = string.Empty;
            for (var i = 0; i < str.Length; i++)
            {
                if (char.IsUpper(str[i])) res += i + " ";
            }

            return res.Split(' ').Where(x => !string.IsNullOrEmpty(x)).Select(int.Parse).ToArray();
        }

        public static string ReplaceVowels(string str, string ch)
        {
            foreach (var letter in str)
            {
                if (isVowel(letter)) str.Replace(letter, ch[0]);
            }
            return str;
        }
        public static bool isVowel(char ch)
        {
            ch = char.ToUpper(ch);
            return (ch == 'A' || ch == 'E' ||
                    ch == 'I' || ch == 'O' ||
                    ch == 'U');
        }

        public double[] FindLargest(double[][] values)
        {
            var cnt = 0;
            var resArr = new double[] { 0, 0, 0 };
            foreach (var arr in values)
            {
                resArr[cnt] = arr[0];
                foreach (var num in arr)
                {
                    if (num > resArr[cnt]) resArr[cnt] = num;
                }
                cnt++;
            }
            return resArr;
        }
        public long CalculateExponent(long number, long exponent)
        {
            long res = 1;
            for (var i = 0; i < exponent; i++)
            {
                res *= number;
            }
            return res;
        }

        public int MissingNum(int[] arr)
        {
            for (var i = 0; i < arr.Length - 1; i++)
            {
                for (var j = 0; j < arr.Length - 1; j++)
                {
                    if (arr[j] <= arr[j + 1]) continue;
                    var tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
            for (var i = 0; i < arr.Length - 1; i++)
            {
                if (arr[i + 1] - arr[i] > 1) return arr[i + 1] - 1;
            }
            return arr[0] == 2 ? 1 : 10;
        }
    }

}
