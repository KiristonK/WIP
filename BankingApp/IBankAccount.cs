using System;

namespace BankingApp
{
    public interface IBankAccount
    {
        Guid AccountNumber { get; }
        decimal Money { get; set; }
        bool Transaction(IBankAccount bankAccount, decimal amount);
        bool GetMoney(decimal amount);
    }
}