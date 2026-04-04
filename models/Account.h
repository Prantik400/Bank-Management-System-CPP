#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;
class Account
{
public:
    int accountId;
    std::string name;
    double balance;
    int pin;

    //  NEW: Transaction History
    vector<Transaction> transactions; // Store Transaction objects 
    // 🔹 Constructor
    Account(int id, std::string n, double bal, int p)
    {
        accountId = id;
        name = n;
        balance = bal;
        pin = p;
    }

    // 🔹 Default Constructor (IMPORTANT)
    Account() {}

    // 🔹 Add transaction
    void addTransaction(const Transaction &t)
    {
        transactions.push_back(t);
    }
};

#endif