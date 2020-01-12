using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json.Linq;

namespace ExamAppWinForm
{
    class CurrencyOperations : ICurrencyData
    {
        private JObject data;

        public JToken GetData(string baseCur)
        {
            var client = new HttpClient();

            string result;
            if (baseCur != null)
            {
                result = client.GetStringAsync("https://api.exchangeratesapi.io/latest?base=" +
                                               baseCur).Result;
                return JObject.Parse(result)["rates"];

                //var i = 0;
                //foreach (var cur in data["rates"])
                //{
                //    var res = Regex.Replace(cur.ToString(), "\"", string.Empty);
                //    fromComBox.Items[i] = res;
                //    toComBox.Items[i] = res;
                //}

                //var baseCur = Regex.Replace(data["base"].ToString(), "\"", string.Empty);
                //fromComBox.SelectedItem = baseCur;
            }
            result = client.GetStringAsync("https://api.exchangeratesapi.io/latest?base=PLN").Result;
            return  JObject.Parse(result)["rates"];

            //foreach (var cur in data["rates"])
            //{
            //    var res = Regex.Replace(cur.ToString(), "\"", string.Empty);
            //    fromComBox.Items.Add(res);
            //    toComBox.Items.Add(res);
            //    if (res.Substring(0, 3) != "PLN") continue;
            //    fromComBox.SelectedItem = res;
            //    toComBox.SelectedItem = res;
            //}
        }

        public double GetCurrency(string currency)
        {
            return data["rates"][currency].Value<double>();
        }

        public double ConvertCurrency(double currency, int amount)
        {
            return currency * amount;
        }
    }
}
