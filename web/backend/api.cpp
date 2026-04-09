#include <iostream>
#include <string>
#include "../../data/DataManager.h"
#include "../../models/Transaction.h"
#include "../../database/db.h"
#include "../../core/AccountOperations.h"
using namespace std;

int main(int argc, char* argv[])
{
    DataManager dm;

    if (argc < 2)
    {
        cout << "Invalid request";
        return 0;
    }

    string action = argv[1];

    // ================= BALANCE =================
    if (action == "balance")
    {
        string id = argv[2];

        Account* acc = dm.findAccountById(id);

        if (acc)
        {
            cout << acc->balance;
            delete acc;
        }
        else
        {
            cout << "ERROR";
        }
    }

    // ================= DEPOSIT =================
    else if (action == "deposit")
{
    string id = argv[2];
    double amount = stod(argv[3]);

    Account* acc = dm.findAccountById(id);

    if (!acc)
    {
        cout << "ERROR";
        return 0;
    }

    if (AccountOperations::deposit(*acc, amount))
    {
        dm.updateBalance(id, acc->balance);
        dm.addTransaction(id, "Deposited by Self", amount, acc->balance);
        cout << "SUCCESS";
    }
    else
    {
        cout << "ERROR";
    }

    delete acc;
}

    // ================= WITHDRAW =================
    else if (action == "withdraw")
    {
        string id = argv[2];
        double amount = stod(argv[3]);

        Account* acc = dm.findAccountById(id);

        if (!acc)
        {
            cout << "ERROR";
            return 0;
        }

        if (AccountOperations::withdraw(*acc, amount))
        {
            dm.updateBalance(id, acc->balance);
            dm.addTransaction(id, "Withdrawn by Self", amount, acc->balance);
            cout << "SUCCESS";
        }
        else
        {
            cout << "ERROR";
        }

        delete acc;
    }

    // ================= TRANSFER =================
    else if (action == "transfer")
    {
    string from = argv[2];
    string to = argv[3];
    double amount = stod(argv[4]);

    Account* sender = dm.findAccountById(from);
    Account* receiver = dm.findAccountById(to);

    if (!sender || !receiver)
    {
        cout << "ERROR";
        return 0;
    }

    if (AccountOperations::transfer(*sender, *receiver, amount))
    {
        dm.updateBalance(from, sender->balance);
        dm.updateBalance(to, receiver->balance);

        dm.addTransaction(from, "Sent to " + to, amount, sender->balance);
        dm.addTransaction(to, "Received from " + from, amount, receiver->balance);

        cout << "SUCCESS";
    }
    else
    {
        cout << "ERROR";
    }

    delete sender;
    delete receiver;
    }
    else if (action == "transactions")
{
    string id = argv[2];

    vector<Transaction> txns = dm.getTransactions(id);

    for (auto &t : txns)
    {
        cout << t.type << "," << t.amount << "," << t.balanceAfter << "," << t.timestamp << endl;
    }
}

    return 0;
}