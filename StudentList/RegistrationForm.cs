using System;
using System.Drawing;
using System.Windows.Forms;


namespace StudentList
{
    public partial class RegistrationForm : Form
    {
        /// <summary>
        /// Let's imagine thar here we have MySQL or any other data base connection :)
        /// </summary>
        private string username = "Username1";
        private string password = "password!@#456";
        public RegistrationForm()
        {
            InitializeComponent();
            textBox3.Hide();
            label2.SendToBack();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button2_Click(object sender, EventArgs e)
        {
           if (textBox1.Text == username && textBox2.Text == password)
           {
               Hide();
               Form1 form1 = new Form1();
               form1.Show();
           }
           else
           {
               label2.ForeColor = Color.Red;
               label2.Top = 211;
               label2.Text = @"Error ! Check username or password !";
           }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label2.Text = "";
            textBox3.Show();
            textBox3.ForeColor = Color.Red;
            if (textBox3.Text != @"Confirm password")
                if (RegisterCheck())
                {
                    textBox3.Hide();
                    label2.Top -= 10;
                    label2.Text = $"Success ! Account created !\n now you can Log In !";
                    textBox1.Text = "";
                    textBox2.Text = "";
                }
        }
        private bool RegisterCheck()
        {
            if (textBox2.Text == textBox3.Text)
            {
                username = textBox1.Text;
                password = textBox2.Text;
                return true;
            }
            textBox2.Text = @"Passwords are not similar !";
            textBox2.ForeColor = Color.Red;
            return false;
        }
        private Point lastPoint;
        private void RegistrationForm_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Left += e.X - lastPoint.X;
                Top += e.Y - lastPoint.Y;
            }
        }

        private void RegistrationForm_MouseDown(object sender, MouseEventArgs e)
        {
            lastPoint = new Point(e.X, e.Y);
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            textBox2.ForeColor = Color.Black;
        }

        private void textBox3_Enter(object sender, EventArgs e)
        {
            textBox3.Text = "";
        }

        private void label3_MouseHover(object sender, EventArgs e)
        {
            label3.BackColor = Color.Red;
        }

        private void label3_MouseLeave(object sender, EventArgs e)
        {
            label3.BackColor = Color.Turquoise;
        }
    }
}