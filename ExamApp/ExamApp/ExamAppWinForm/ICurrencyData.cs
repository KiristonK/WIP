using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json.Linq;

namespace ExamAppWinForm
{
    interface ICurrencyData
    {
        JToken GetData(string _);
        double GetCurrency(string _);
        double ConvertCurrency(double _, int __);
    }
}
