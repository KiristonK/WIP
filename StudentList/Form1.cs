using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace StudentList
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Student student = new Student();
            student.AddStudent(ref students, ref name, ref surname, ref phone);
            name.Text = "";
            surname.Text = "";
            phone.Text = "";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (students.SelectedIndex != -1)
                students.Items.RemoveAt(students.SelectedIndex);
        }

        private void students_MouseClick(object sender, MouseEventArgs e)
        {
            students.SelectedIndex = students.IndexFromPoint(e.Location);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Application.Exit();
        }
    }

    public class Student
    {
        private string FirstName { get; set; }
        private string LastName { get; set; }
        private string PhoneNumber { get; set; }

        public void AddStudent(ref ListBox listBox, ref TextBox name, ref TextBox surname, ref TextBox phone)
        {
            if (name.Text == "" || IsDigit(name.Text) || surname.Text == "" || IsDigit(surname.Text) || phone.Text == "" || !IsDigitOnly(phone.Text))
            {
                MessageBox.Show($@"Fields name and surname can not be empty or contain digits
Phone number must be with digits only !", @"Error 0");
                return;
            }
            FirstName = name.Text;
            LastName = surname.Text;
            PhoneNumber = phone.Text;
            listBox.Items.Add(item: $"{listBox.Items.Count + 1}: Student : {FirstName} {LastName}, +48{PhoneNumber}");
        }

        private bool IsDigit(string tmp)
        {
            return tmp.Any(i => i >= '0' && i <= '9');
        }
        private bool IsDigitOnly(string tmp)
        {
            if (tmp == "") return false;
            foreach (var i in tmp)
                if (i >= '0' && i <= '9') { }
                else
                    return false;
            return true;
        }
    }
}
