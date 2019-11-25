using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace StudentList
{
    public class Student
    {
        public static readonly List<Student> Students = new List<Student>();
        private int Id { get; set; }
        public string FirstName { get; private set; }
        public string LastName { get;private  set; }
        public string PhoneNumber { get;private set; }

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
            Id = listBox.Items.Count + 1;
            listBox.Items.Add(this);
            Students.Add(this);
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

        public override string ToString()
        {
            return $"{Id}: Student : {FirstName} {LastName}, +48{PhoneNumber}";
        }
    }
}
