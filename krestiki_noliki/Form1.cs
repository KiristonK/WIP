using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace krestiki_noliki
{
    public partial class Form1 : Form
    {
        private bool button1Click = false;
        public Form1()
        {
            InitializeComponent();
        }
 
        private void Button1_Click(object sender, EventArgs e)
        {
            label2.Text += "человеком.";
            label2.Visible = true;
            button1.Enabled = false;
            button2.Enabled = false;
            button1Click = true;
            WhoIsNext(sender, e);
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            label2.Text += "компьютером.";
            label2.Visible = true;
            button1.Enabled = false;
            button2.Enabled = false;
        }
        
        private bool WhoIsNext(object sender, EventArgs e)
        {
            if (button1Click == true)
            {
                label4.Text = "Ход Человека";
                label4.Visible = true;
            }
            else
            {
                label4.Text = "Ход Компьютера";
                label4.Visible = true;
            }
            return button1Click;
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            if (WhoIsNext(sender, e))
            {
                button3.Text = "X";
                button1Click = false;
            }
        }
    }
}
