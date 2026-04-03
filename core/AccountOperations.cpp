#include "AccountOperations.h"

namespace AccountOperations
{
bool deposit(Account &acc, double amount)
{
    if (amount <= 0)
    {
        return false; // Cannot deposit a negative amount
    }
    acc.balance += amount;
    return true;
}

bool withdraw(Account &acc, double amount)
{
    if (amount <= 0 || amount > acc.balance)
    {
        return false; // Cannot withdraw a negative amount or more than the balance
    }
    acc.balance -= amount;
    return true;
}

bool transfer(Account &sender, Account &receiver, double amount)
{
    if (amount <= 0)
    {
        return false; // Cannot deposit a negative amount
    }
    sender.balance -= amount;
    receiver.balance += amount;
    return true;
}

double checkBalance(const Account &acc)
{
    return acc.balance;
}
}