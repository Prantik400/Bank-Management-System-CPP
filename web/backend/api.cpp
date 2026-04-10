#include <iostream>
#include <string>
#include <vector>
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

    // ================= LOGIN =================
    if (action == "login")
    {
        if (argc < 4) { cout << "INVALID"; return 0; }

        string id = argv[2];
        string pinStr = argv[3];

        // ADMIN LOGIN
        if (id == "admin" && pinStr == "admin123")
        {
            cout << "ADMIN";
            return 0;
        }

        for(char c: pinStr) {
            if (!isdigit(c)) {
                cout << "INVALID";
                return 0;
            }
        }

        int pin = stoi(pinStr);

        Account* acc = dm.findAccountById(id);

        if (!acc || acc->pin != pin)
        {
            cout << "INVALID";
            if (acc) delete acc;
            return 0;
        }

        cout << "USER:" << acc->name;
        delete acc;
        return 0;
    }

    // ================= BALANCE =================
    else if (action == "balance")
    {
        if (argc < 3) { cout << "ERROR"; return 0; }

        string id = argv[2];
        Account* acc = dm.findAccountById(id);

        if (acc)
        {
            cout << acc->balance;
            delete acc;
        }
        else cout << "ERROR";

        return 0;
    }

    // ================= DEPOSIT =================
    else if (action == "deposit")
    {
        if (argc < 4) { cout << "ERROR"; return 0; }

        string id = argv[2];
        double amount = stod(argv[3]);

        if (amount <= 0) { cout << "ERROR"; return 0; }

        Account* acc = dm.findAccountById(id);

        if (!acc) { cout << "ERROR"; return 0; }

        if (AccountOperations::deposit(*acc, amount))
        {
            dm.updateBalance(id, acc->balance);
            dm.addTransaction(id, "Deposited by Self", amount, acc->balance);
            cout << "SUCCESS";
        }
        else cout << "ERROR";

        delete acc;
        return 0;
    }

    // ================= WITHDRAW =================
    else if (action == "withdraw")
    {
        if (argc < 4) { cout << "ERROR"; return 0; }

        string id = argv[2];
        double amount = stod(argv[3]);

        if (amount <= 0) { cout << "ERROR"; return 0; }

        Account* acc = dm.findAccountById(id);

        if (!acc) { cout << "ERROR"; return 0; }

        if (AccountOperations::withdraw(*acc, amount))
        {
            dm.updateBalance(id, acc->balance);
            dm.addTransaction(id, "Withdrawn by Self", amount, acc->balance);
            cout << "SUCCESS";
        }
        else cout << "ERROR";

        delete acc;
        return 0;
    }

    // ================= TRANSFER =================
    else if (action == "transfer")
    {
        if (argc < 5) { cout << "ERROR"; return 0; }

        string from = argv[2];
        string to = argv[3];
        double amount = stod(argv[4]);

        if (amount <= 0) { cout << "ERROR"; return 0; }

        Account* sender = dm.findAccountById(from);
        Account* receiver = dm.findAccountById(to);

        if (!sender || !receiver)
        {
            if (sender) delete sender;
            if (receiver) delete receiver;
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
        else cout << "ERROR";

        delete sender;
        delete receiver;
        return 0;
    }

    // ================= TRANSACTIONS =================
    else if (action == "transactions")
    {
        if (argc < 3) { cout << "ERROR"; return 0; }

        string id = argv[2];

        if (id == "ALL") // ADMIN
        {
            vector<Account> accounts = dm.getAllAccounts();

            for (auto &acc : accounts)
            {
                vector<Transaction> txns = dm.getTransactions(acc.accountId);

                for (auto &t : txns)
                {
                    cout << t.type << ","
                         << t.amount << ","
                         << t.balanceAfter << ","
                         << t.timestamp << endl;
                }
            }
        }
        else
        {
            vector<Transaction> txns = dm.getTransactions(id);

            for (auto &t : txns)
            {
                cout << t.type << ","
                     << t.amount << ","
                     << t.balanceAfter << ","
                     << t.timestamp << endl;
            }
        }

        return 0;
    }

    // ================= CHANGE PIN =================
    else if (action == "changePin")
    {
    if (argc < 5)
    {
        cout << "ERROR";
        return 0;
    }

    string id = argv[2];
    int oldPin = stoi(argv[3]);
    int newPin = stoi(argv[4]);

    // 🔹 Step 1: Fetch account
    Account* acc = dm.findAccountById(id);

    if (!acc)
    {
        cout << "ERROR";
        return 0;
    }

    // 🔹 Step 2: Check old PIN
    if (acc->pin != oldPin)
    {
        cout << "WRONG_PIN";
        delete acc;
        return 0;
    }

    delete acc;

    // 🔹 Step 3: Update PIN directly using DB
    MYSQL* conn = DB::connect();

    string query = "UPDATE accounts SET pin = " + to_string(newPin) +
                   " WHERE account_id = '" + id + "'";

    if (mysql_query(conn, query.c_str()))
    {
        cout << "ERROR";
    }
    else
    {
        cout << "SUCCESS";
    }

    mysql_close(conn);
    }

    // ================= CREATE ACCOUNT =================
    else if (action == "create")
    {
        if (argc < 5) { cout << "ERROR"; return 0; }

        string id = argv[2];
        int pin = stoi(argv[3]);
        string name = argv[4];

        Account newAcc;
        newAcc.accountId = id;
        newAcc.pin = pin;
        newAcc.name = name;
        newAcc.balance = 0;

        dm.createAccount(newAcc);
        cout << "SUCCESS";

        return 0;
    }

    // ================= DELETE ACCOUNT =================
    else if (action == "delete")
    {
        if (argc < 3) { cout << "ERROR"; return 0; }

        string id = argv[2];

        if (dm.deleteAccount(id))
            cout << "SUCCESS";
        else
            cout << "ERROR";

        return 0;
    }

    // ================= VIEW ALL ACCOUNTS =================
    else if (action == "allAccounts")
    {
        vector<Account> accounts = dm.getAllAccounts();

        for (auto &acc : accounts)
        {
            cout << acc.accountId << ","
                 << acc.name << ","
                 << acc.balance << endl;
        }

        return 0;
    }

    // ================= TOTAL BALANCE =================
    else if (action == "total")
    {
        vector<Account> accounts = dm.getAllAccounts();

        double total = 0;
        for (auto &acc : accounts)
            total += acc.balance;

        cout << total;
        return 0;
    }

    else
    {
        cout << "Invalid action";
    }

    return 0;
}