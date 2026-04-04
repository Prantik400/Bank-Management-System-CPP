#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction
{
    public:
    string type; //Deposit, Withdraw, Transfer
    double amount;
    double balanceAfter; // NEW: Store balance after transaction
    string timestamp;

    Transaction(string t, double amt, double bal, string time);
};

#endif