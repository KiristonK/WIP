using System;
using System.Drawing;
using System.Windows.Forms;

namespace StudentList
{
    public partial class Form1 : Form
    {
        private Point _lastPoint;
        public Form1()
        {
            InitializeComponent();
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            Student student = new Student();
            student.AddStudent(ref students, ref name, ref surname, ref phone);
            name.Text = "";
            surname.Text = "";
            phone.Text = "";
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            if (students.SelectedIndex != -1)
                students.Items.RemoveAt(students.SelectedIndex);
        }

        private void students_MouseClick(object sender, MouseEventArgs e)
        {
            students.SelectedIndex = students.IndexFromPoint(e.Location);
            var dataList = students.Items[students.SelectedIndex].ToString().Replace(":","").Split();
            name.Text = Student.Students[students.SelectedIndex].FirstName;
            surname.Text = Student.Students[students.SelectedIndex].LastName;
            phone.Text = Student.Students[students.SelectedIndex].PhoneNumber;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Application.Exit();
        }

        private void CloseBtn_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void CloseBtn_MouseEnter(object sender, EventArgs e)
        {
            CloseBtn.BackColor  = Color.Red;
        }

        private void CloseBtn_MouseLeave(object sender, EventArgs e)
        {
            CloseBtn.BackColor = Color.LightGray;
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Left += e.X - _lastPoint.X;
                Top += e.Y - _lastPoint.Y;
            }
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            _lastPoint = new Point(e.X, e.Y);
        }

        public void AddUsername(string usernameText)
        {
           LoggedUser.Text = $@"Username : {usernameText}";
        }

        private void name_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                surname.Focus();
                e.Handled = e.SuppressKeyPress = true;
            }
        }

        private void surname_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                phone.Focus();
                e.Handled = e.SuppressKeyPress = true;
            }
        }

        private void phone_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                btnAdd.PerformClick();
                e.Handled = e.SuppressKeyPress = true;
            }
        }
    }
}
