using System;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using Newtonsoft.Json;

namespace ExamAppWinForm
{
    public partial class Form1 : Form
    {
        private readonly CurrencyOperations _co = new CurrencyOperations();

        public Form1()
        {
            InitializeComponent();
            InitBoxes("PLN", "CAD");
        }

        private double Currency { get; set; }

        private void InitBoxes(string baseCur, string toCurrency)
        {
            FromComBox.Items.Clear();
            ToComBox.Items.Clear();
            foreach (var item in _co.GetData(baseCur))
            {
                var res = Regex.Replace(item.ToString(), "\"", string.Empty);

                if (item.ToString().Substring(1, 3) == baseCur)
                {
                    var indexFrom = FromComBox.Items.Add(res);
                    FromComBox.SelectedIndex = indexFrom;
                }
                else
                {
                    FromComBox.Items.Add(res);
                }

                if (item.ToString().Substring(1, 3) == toCurrency)
                {
                    var indexTo = ToComBox.Items.Add(res);
                    ToComBox.SelectedIndex = indexTo;
                }
                else
                {
                    ToComBox.Items.Add(res);
                }
            }

            Currency = double.Parse(Regex.Replace(ToComBox.SelectedItem.ToString(),
                ".*?: ", string.Empty));
            Result();
            SetLabels();
        }

        private void Result()
        {
            if (int.TryParse(FromAmount.Text, out var r))
                ResultAmount.Text = _co.ConvertCurrency(Currency, r).ToString();
        }

        private void SetLabels()
        {
            StartCurrency.Text = FromComBox.SelectedItem.ToString().Substring(0, 3);
            EndCurrency.Text = ToComBox.SelectedItem.ToString().Substring(0, 3);
            ResultLabel.Text = ToComBox.SelectedItem.ToString().Substring(0, 3);
        }

        private void Input_TextChanged(object sender, EventArgs e)
        {
            Result();
        }

        private void SwitchCurrencies_Click(object sender, EventArgs e)
        {
            var tmp = FromComBox.SelectedItem;
            FromComBox.SelectedItem = ToComBox.SelectedItem;
            ToComBox.SelectedItem = tmp;
            InitBoxes(FromComBox.SelectedItem.ToString().Substring(0, 3),
                ToComBox.SelectedItem.ToString().Substring(0, 3));
        }

        private void FromComBox_SelectedValueChanged(object sender, EventArgs e)
        {
            InitBoxes(FromComBox.SelectedItem.ToString().Substring(0, 3),
                ToComBox.SelectedItem.ToString().Substring(0, 3));
        }

        private void ToComBox_SelectedValueChanged(object sender, EventArgs e)
        {
            Currency = double.Parse(Regex.Replace(ToComBox.SelectedItem.ToString(),
                ".*?: ", string.Empty));
            Result();
            SetLabels();
        }

        private void SaveAsJson(object sender, EventArgs e)
        {
            var serializer = new JsonSerializer();
            using (var sw = new StreamWriter(@"ExchangeResult.json"))
            using (JsonWriter writer = new JsonTextWriter(sw))
            {
                serializer.Serialize(writer, new
                {
                    BaseCurrency = FromComBox.SelectedItem.ToString().Substring(0, 3),
                    Amount = FromAmount.Text,
                    Currency = ToComBox.SelectedItem.ToString(),
                    ResultAmount = ResultAmount.Text +
                                   ToComBox.SelectedItem.ToString().Substring(0, 3)
                });
            }
        }

        private void ExitApplication(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void SaveAsTxt(object sender, EventArgs e)
        {
            var stringBuilder = new StringBuilder();
            stringBuilder.AppendLine("Base currency: " + FromComBox.SelectedItem.ToString().Substring(0, 3));
            stringBuilder.AppendLine("Aim currency: " + ToComBox.SelectedItem);
            stringBuilder.AppendLine("Amount: " + FromAmount.Text);
            stringBuilder.AppendLine("You will get " + ResultAmount.Text + " " +
                                     ToComBox.SelectedItem.ToString().Substring(0, 3));

            using (var sw = new StreamWriter(@"ExchangeResult.txt"))
            {
                sw.Write(stringBuilder);
            }
        }
    }
}