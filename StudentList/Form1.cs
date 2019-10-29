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

    
}
