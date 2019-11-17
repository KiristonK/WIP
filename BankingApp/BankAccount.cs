using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace BankingApp
{
    class BankAccount : IBankAccount
    {
        private string Name { get; }
        private string Surname { get; }
        private DateTime DateOfBirth { get; }
        public Guid AccountNumber { get; }
        private decimal Money { get; set; }

        decimal IBankAccount.Money
        {
            get => this.Money;
            set => this.Money = value;
        }

        public bool Transaction(IBankAccount bankAccount, decimal amount)
        {
            try
            {
                bankAccount.Money += amount;
                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return false;
            }
        }

        public bool GetMoney(decimal amount)
        {
            if (amount <= this.Money)
            {
                this.Money -= amount;
                return true;
            }

            MessageBox.Show("Not enough money on account !");
            return false;
        }

        public BankAccount(string name, string surname, DateTime dateOfBirth)
        {
            Name = name;
            Surname = surname;
            DateOfBirth = dateOfBirth;
            AccountNumber = Guid.NewGuid();
        }
    }
}
