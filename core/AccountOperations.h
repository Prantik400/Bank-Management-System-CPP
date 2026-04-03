#ifndef CORE_ACCOUNT_OPERATIONS_H
#define CORE_ACCOUNT_OPERATIONS_H

#include "../models/Account.h"
namespace AccountOperations
{
bool deposit(Account &acc, double amount);
bool withdraw(Account &acc, double amount); 
bool transfer(Account &sender, Account &receiver, double amount);
double checkBalance(const Account &acc);
} // namespace AccountOperations

#endif