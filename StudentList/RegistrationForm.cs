using System;
using System.Drawing;
using System.Windows.Forms;

namespace StudentList
{
    public partial class RegistrationForm : Form
    {
        private DataBase _db;
        public RegistrationForm()
        {
            InitializeComponent();
            passwordConfirm.Hide();
            errorLabel.SendToBack();

        }

        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void logIn_Click(object sender, EventArgs e)
        {
            string usernameText = username.Text, passwordText = password.Text;  
           if (_db.CheckInDataBase(usernameText,password: passwordText))
           {
               Hide();
               Form1 form1 = new Form1();
               form1.Show();
               form1.AddUsername(usernameText);
           }
           else
           {
               errorLabel.ForeColor = Color.Red;
               errorLabel.Top = 211;
               errorLabel.Text = @"Error ! Check username or password !";
           }
        }

        private void signIn_Click(object sender, EventArgs e)
        {
            errorLabel.Text = "";
            passwordConfirm.Show();
            passwordConfirm.ForeColor = Color.Red;
            if (passwordConfirm.Text != @"Confirm password")
                if (RegisterCheck())
                {
                    passwordConfirm.Hide();
                    errorLabel.Top -= 10;
                    errorLabel.Text = @"Success ! Account created !
Now you can Log In !";
                    username.Text = "";
                    password.Text = "";
                }
        }
        private bool RegisterCheck()
        {
            if (password.Text == passwordConfirm.Text)
            {
                _db.AddUser(username.Text, password.Text);
                if (_db.CheckInDataBase(username.Text, password.Text))
                    return true;
                MessageBox.Show(@"Something went wrong during adding record to database", @"Error",
                    MessageBoxButtons.OK);
                return false;
            }
            password.Text = @"Passwords are not similar !";
            password.ForeColor = Color.Red;
            return false;
        }
        private Point _lastPoint;
        private void RegistrationForm_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Left += e.X - _lastPoint.X;
                Top += e.Y - _lastPoint.Y;
            }
        }

        private void RegistrationForm_MouseDown(object sender, MouseEventArgs e)
        {
            _lastPoint = new Point(e.X, e.Y);
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
            closeBtn.BackColor = Color.Red;
        }

        private void label3_MouseLeave(object sender, EventArgs e)
        {
            closeBtn.BackColor = Color.Turquoise;
        }

        private void RegistrationForm_Load(object sender, EventArgs e)
        {
            _db = new DataBase();
            _db.OpenConnection();
        }

        private void password_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                logIn_Click(sender,e);
            }
        }

        private void passwordConfirm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                signIn_Click(sender,e);
            }
        }
    }
}