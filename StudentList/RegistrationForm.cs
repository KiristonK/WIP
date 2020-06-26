using System;
using System.Drawing;
using System.Windows.Forms;

namespace StudentList
{
    public partial class RegistrationForm : Form
    {
        private DataBase _db;
        private Point _lastPoint;
        public RegistrationForm()
        {
            InitializeComponent();
            passwordConfirm.Hide();
            errorLabel.SendToBack();

        }

        private void Button3_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void LogIn_Click(object sender, EventArgs e)
        {
            string usernameText = username.Text, passwordText = password.Text;  
           if (_db.CheckInDataBase(usernameText,password: passwordText)) //If user exists open main form and hide current, else show error message
           {
               Hide();
               Form1 form1 = new Form1();
               form1.Show();
               form1.AddUsername(usernameText);
           }
           else //Set error message
           {
               errorLabel.ForeColor = Color.Red;
               errorLabel.Top = 211;
               errorLabel.Text = @"Error ! Check username or password !";
           }
        }

        private void SignIn_Click(object sender, EventArgs e)
        {
            errorLabel.Text = "";
            passwordConfirm.Show();
            passwordConfirm.ForeColor = Color.Red;
            if (passwordConfirm.Text == @"Confirm password") return; //If second password field not filled - return
            if (!RegisterCheck()) return; //If any error occurs while adding new user - return
            passwordConfirm.Hide();
            errorLabel.Top -= 10;
            errorLabel.Text = @"Success ! Account created !
Now you can Log In !";
            username.Text = "";
            password.Text = "";
        }

        private bool RegisterCheck()
        {
            if (password.Text == passwordConfirm.Text) //If passwords are similar
            {
                _db.AddUser(username.Text, password.Text);
                if (_db.CheckInDataBase(username.Text, password.Text)) //If user exists
                    return true;
                MessageBox.Show(@"Something went wrong during adding record to database", @"Error",
                    MessageBoxButtons.OK);
                return false;
            }
            password.Text = @"Passwords are not similar !";
            password.ForeColor = Color.Red;
            return false;
        }

        private void RegistrationForm_MouseMove(object sender, MouseEventArgs e) //Window moving by mouse left click&hold
        {
            if (e.Button != MouseButtons.Left) return;
            Left += e.X - _lastPoint.X;
            Top += e.Y - _lastPoint.Y;
        }

        private void RegistrationForm_MouseDown(object sender, MouseEventArgs e)
        {
            _lastPoint = new Point(e.X, e.Y);
        }

        private void TextBox2_TextChanged(object sender, EventArgs e)
        {
            password.ForeColor = Color.Black;
        }

        private void TextBox3_Enter(object sender, EventArgs e)
        {
            passwordConfirm.Text = "";
        }

        private void Label3_MouseHover(object sender, EventArgs e)
        {
            closeBtn.BackColor = Color.Red;
        }

        private void Label3_MouseLeave(object sender, EventArgs e)
        {
            closeBtn.BackColor = Color.Turquoise;
        }

        private void RegistrationForm_Load(object sender, EventArgs e)
        {
            _db = new DataBase();
            _db.OpenConnection();
        }

        private void Password_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode != Keys.Enter) return;
            logIn.PerformClick();
            e.Handled = e.SuppressKeyPress = true;
        }

        private void passwordConfirm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode != Keys.Enter) return;
            SignIn_Click(sender,e);
            e.Handled = e.SuppressKeyPress = true;
        }

        private void username_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char) Keys.Enter)
            {
                password.Focus();
            }
        }
    }
}