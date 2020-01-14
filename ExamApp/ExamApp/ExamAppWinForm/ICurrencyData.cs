using Newtonsoft.Json.Linq;

namespace ExamAppWinForm
{
    internal interface ICurrencyData
    {
        JToken GetData(string _);
        double GetCurrency(string _);
        double ConvertCurrency(double _, int __);
    }
}