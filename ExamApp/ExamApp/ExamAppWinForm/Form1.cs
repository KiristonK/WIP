using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Http;
using System.Text.RegularExpressions;
using System.Threading;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace ExamAppWinForm
{
    public partial class Form1 : Form
    {
        private readonly CurrencyOperations _co = new CurrencyOperations();
        private double Currency { get; set; }

        public Form1()
        {
            InitializeComponent();

            foreach (var item in _co.GetData(null))
            {
                var res = Regex.Replace(item.ToString(), "\"", string.Empty);

                if (item.ToString().Substring(1, 3) == "PLN")
                {
                    var index = this.FromComBox.Items.Add(res);
                    this.FromComBox.SelectedIndex = index;
                }
                else
                    this.FromComBox.Items.Add(res);
            }

            foreach (var item in _co.GetData(null))
            {
                var res = Regex.Replace(item.ToString(), "\"", string.Empty);
                this.ToComBox.Items.Add(res);
            }
            this.ToComBox.SelectedIndex = 0;
            SetLabels();
        }


        private void InitBoxes(string baseCur, string toCurrency)
        {
            this.FromComBox.Items.Clear();
            this.ToComBox.Items.Clear();
            foreach (var item in _co.GetData(baseCur))
            {
                var res = Regex.Replace(item.ToString(), "\"", string.Empty);

                if (item.ToString().Substring(1, 3) == baseCur)
                {
                    var indexFrom = this.FromComBox.Items.Add(res); 
                    this.FromComBox.SelectedIndex = indexFrom;
                }
                else
                    this.FromComBox.Items.Add(res);

                if (item.ToString().Substring(1, 3) == toCurrency)
                {
                    var indexTo = this.ToComBox.Items.Add(res);
                    this.ToComBox.SelectedIndex = indexTo;
                }
                else
                    this.ToComBox.Items.Add(res);
            }
        }


        private void SetLabels()
        {
            this.StartCurrency.Text = FromComBox.SelectedItem.ToString().Substring(0, 3);
            this.EndCurrency.Text = ToComBox.SelectedItem.ToString().Substring(0, 3);
            this.ResultLabel.Text = ToComBox.SelectedItem.ToString().Substring(0, 3);
        }

        private void Input_TextChanged(object sender, EventArgs e)
        {
            if (int.TryParse(FromAmount.Text, out var r))
                ResultAmount.Text = _co.ConvertCurrency(Currency,r).ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var tmp = FromComBox.SelectedItem;
            FromComBox.SelectedItem = ToComBox.SelectedItem;
            ToComBox.SelectedItem = tmp;
            InitBoxes(this.FromComBox.SelectedItem.ToString().Substring(0, 3), 
                this.ToComBox.SelectedItem.ToString().Substring(0, 3));
            Currency = double.Parse(Regex.Replace(this.ToComBox.SelectedItem.ToString(),
                ".*?: ", string.Empty));
            SetLabels();

        }


        private void FromComBox_SelectedValueChanged(object sender, EventArgs e)
        {
            //InitBoxes(this.FromComBox.SelectedItem.ToString().Substring(0, 3),
            //    this.ToComBox.SelectedItem.ToString().Substring(0, 3));
            Currency = double.Parse(Regex.Replace(this.ToComBox.SelectedItem.ToString(),
                ".*?: ", string.Empty));
            SetLabels();
        }

        private void ToComBox_SelectedValueChanged(object sender, EventArgs e)
        {
            Currency = double.Parse(Regex.Replace(this.ToComBox.SelectedItem.ToString(),
                ".*?: ", string.Empty));
            SetLabels();
        }
    }
}
