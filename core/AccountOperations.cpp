#include "AccountOperations.h"

namespace AccountOperations
{

bool deposit(Account &acc, double amount)
{
    if (amount <= 0)
    {
        return false;
    }

    acc.balance += amount;
    return true;
}

bool withdraw(Account &acc, double amount)
{
    if (amount <= 0 || amount > acc.balance)
    {
        return false;
    }

    acc.balance -= amount;
    return true;
}

bool transfer(Account &sender, Account &receiver, double amount)
{
    //  Proper validation
    if (amount <= 0 || amount > sender.balance)
    {
        return false;
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