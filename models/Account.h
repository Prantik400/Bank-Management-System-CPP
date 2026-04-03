#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Account
{
public:
    int accountId;
    std::string name;
    double balance;
    int pin;

    // 🔥 NEW: Transaction History
    std::vector<std::string> transactionHistory;

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
    void addTransaction(const std::string &transaction)
    {
        transactionHistory.push_back(transaction);
    }
};

#endif