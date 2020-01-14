using System.Net.Http;
using Newtonsoft.Json.Linq;

namespace ExamAppWinForm
{
    internal class CurrencyOperations : ICurrencyData
    {
        public JToken GetData(string baseCur)
        {
            var client = new HttpClient();

            string result;
            if (baseCur != null)
            {
                result = client.GetStringAsync("https://api.exchangeratesapi.io/latest?base=" +
                                               baseCur).Result;
                return JObject.Parse(result)["rates"];
            }

            result = client.GetStringAsync("https://api.exchangeratesapi.io/latest?base=PLN").Result;
            return JObject.Parse(result)["rates"];
        }

        public double GetCurrency(string currency)
        {
            return GetData(currency)[currency].Value<double>();
        }

        public double ConvertCurrency(double currency, int amount)
        {
            return currency * amount;
        }
    }
}