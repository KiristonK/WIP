using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameCSharp.Menu_s.EscapeMenu
{
    public partial class EscapeMenuForm : Form
    {
        public EscapeMenuForm()
        {
            InitializeComponent();
        }

        private void ExitMenu_MouseLeave(object sender, EventArgs e)
        {
            (sender as Label).ForeColor = Color.Black;
        }

        private void ExitMenu_MouseEnter(object sender, EventArgs e)
        {
            (sender as Label).ForeColor = Color.Red;
        }

        private void EscapeMenuForm_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Escape) Close();
        }

        private void ExitMenu_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
