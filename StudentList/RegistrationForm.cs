using System;
using System.Drawing;
using System.Windows.Forms;
using System.Data.Sql;
using System.Data.SqlClient;

namespace StudentList
{
    public partial class RegistrationForm : Form
    {
        /// <summary>
        /// Let's imagine thar here we have MySQL or any other data base connection :)
        /// </summary>
        public RegistrationForm()
        {
            InitializeComponent();
            passwordConfirm.Hide();
            label2.SendToBack();

        }

        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DataBase db = new DataBase();
            db.OpenConnection();
            string usernameText = username.Text, passwordText = password.Text;  
           if (db.CheckInDataBase(usernameText,password: passwordText))
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
            passwordConfirm.Show();
            passwordConfirm.ForeColor = Color.Red;
            if (passwordConfirm.Text != @"Confirm password")
                if (RegisterCheck())
                {
                    passwordConfirm.Hide();
                    label2.Top -= 10;
                    label2.Text = @"Success ! Account created !
Now you can Log In !";
                    username.Text = "";
                    password.Text = "";
                }
        }
        private bool RegisterCheck()
        {
            if (password.Text == passwordConfirm.Text)
            {
                
                return true;
            }
            password.Text = @"Passwords are not similar !";
            password.ForeColor = Color.Red;
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
            password.ForeColor = Color.Black;
        }

        private void textBox3_Enter(object sender, EventArgs e)
        {
            passwordConfirm.Text = "";
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