#include <iomanip>
#include <iostream>
#include "UserMenu.h"
#include "../core/AccountOperations.h"
#include "../models/Transaction.h"
#include "../utils/helpers.h"
#include "../database/db.h"
#include <mysql/mysql.h>

using namespace std;

// Constructor
UserMenu::UserMenu(DataManager& dm, Account* user)
    : dataManager(dm), currentUser(user) {}

// Destructor
UserMenu::~UserMenu() {
    delete currentUser;
}

// ================= PIN =================
bool UserMenu::verifyUserPin()
{
    string pinInput;

    cout << "Enter PIN: ";
    getline(cin, pinInput);
    pinInput = trim(pinInput);

    if (!isNumber(pinInput))
    {
        cout << "Invalid PIN!\n";
        return false;
    }

    if (stoi(pinInput) != currentUser->pin)
    {
        cout << "Incorrect PIN!\n";
        return false;
    }

    return true;
}

// ================= MENU =================
void UserMenu::show()
{
    string input;
    int choice;

    while (true)
    {
        cout << "\n===== USER MENU =====\n";
        cout << "\nWelcome, " << currentUser->name << "!\n\n";
        cout << "\n1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. Transaction History\n";
        cout << "6. Change PIN\n";
        cout << "7. Logout\n";
        cout << "\nEnter choice: ";

        getline(cin, input);
        input = trim(input);

        if (!isNumber(input))
        {
            cout << "Invalid input! Enter a number.\n";
            continue;
        }

        choice = stoi(input);

        switch (choice)
        {
        case 1: checkBalance(); break;
        case 2: deposit(); break;
        case 3: withdraw(); break;
        case 4: transfer(); break;
        case 5: showTransactionHistory(); break;

        case 6:
            changePin();
            return;

        case 7:
            cout << "\nLogging out...\n";
            return;

        default:
            cout << "\nInvalid choice!\n";
        }
    }
}

// ================= BALANCE =================
void UserMenu::checkBalance()
{
    cout<<"\n--------------------\n";
    cout<<"BALANCE SECTION\n";
    cout<<"--------------------\n\n";
    if (!verifyUserPin()) return;

    cout << "\nCurrent Balance: Rs." << currentUser->balance << endl;
}

// ================= DEPOSIT =================
void UserMenu::deposit()
{
    cout<<"\n--------------------\n";
    cout<<"DEPOSIT SECTION\n";
    cout<<"--------------------\n\n";
    
    string input;
    cout << "\nEnter amount to deposit: ";
    getline(cin, input);

    if (!isDouble(input))
    {
        cout << "Invalid input!\n";
        return;
    }

    double amount = stod(input);

    if (amount <= 0 || amount > 10000000)
    {
        cout << "Invalid amount!\n";
        return;
    }

    if (!verifyUserPin()) return;

    currentUser->balance += amount;

    dataManager.updateBalance(currentUser->accountId, currentUser->balance);
    dataManager.addTransaction(currentUser->accountId, "Deposited by Self", amount, currentUser->balance);

    cout << "\nDeposit successful!\n";
}

// ================= WITHDRAW =================
void UserMenu::withdraw()
{
    cout<<"\n--------------------\n";
    cout<<"WITHDRAW SECTION\n";
    cout<<"--------------------\n\n";
    string input;
    cout << "Enter amount to withdraw: ";
    getline(cin, input);

    if (!isDouble(input))
    {
        cout << "Invalid input!\n";
        return;
    }

    double amount = stod(input);

    if (amount <= 0 || amount > 10000000)
    {
        cout << "Invalid amount!\n";
        return;
    }

    if (!verifyUserPin()) return;

    if (!AccountOperations::withdraw(*currentUser, amount))
    {
        cout << "Insufficient balance!\n";
        return;
    }

    dataManager.updateBalance(currentUser->accountId, currentUser->balance);
    dataManager.addTransaction(currentUser->accountId, "Withdrawn by Self", amount, currentUser->balance);

    cout << "\nWithdrawal successful!\n";
}

// ================= TRANSFER =================
void UserMenu::transfer()
{
    cout<<"\n--------------------\n";
    cout<<"TRANSFER SECTION\n";
    cout<<"--------------------\n\n";
    string id, input;

    cout << "Enter receiver ID: ";
    getline(cin, id);
    id = trim(id);

    if (id == currentUser->accountId)
    {
        cout << "Cannot transfer to your own account!\n";
        return;
    }

    Account* receiver = dataManager.findAccountById(id);

    if (!receiver)
    {
        cout << "User not found!\n";
        return;
    }

    cout << "Enter amount: ";
    getline(cin, input);

    if (!isDouble(input))
    {
        cout << "Invalid input!\n";
        delete receiver;
        return;
    }

    double amount = stod(input);

    if (amount <= 0 || amount > 10000000)
    {
        cout << "Invalid amount!\n";
        delete receiver;
        return;
    }

    if (!verifyUserPin())
    {
        delete receiver;
        return;
    }

    if (!AccountOperations::transfer(*currentUser, *receiver, amount))
    {
        cout << "Insufficient balance!\n";
        delete receiver;
        return;
    }

    dataManager.updateBalance(currentUser->accountId, currentUser->balance);
    dataManager.updateBalance(receiver->accountId, receiver->balance);

    string senderMsg = "Sent to " + receiver->accountId + " (" + receiver->name + ")";
    string receiverMsg = "Received from " + currentUser->accountId + " (" + currentUser->name + ")";

    dataManager.addTransaction(currentUser->accountId, senderMsg, amount, currentUser->balance);
    dataManager.addTransaction(receiver->accountId, receiverMsg, amount, receiver->balance);

    cout << "\nTransfer successful!\n";

    delete receiver;
}

// ================= HISTORY =================
void UserMenu::showTransactionHistory()
{
    cout<<"\n--------------------\n";
    cout<<"HISTORY SECTION\n";
    cout<<"--------------------\n\n";
    if (!verifyUserPin()) return;

    vector<Transaction> transactions = dataManager.getTransactions(currentUser->accountId);

    if (transactions.empty())
    {
        cout << "No transactions found!\n";
        return;
    }

    cout << "\n----------------------------------------- Transaction History -----------------------------------------\n\n";

    for (auto &t : transactions)
    {
        cout << left << setw(35) << t.type
             << "| Rs." << setw(10) << t.amount
             << "| Balance: Rs." << setw(12) << t.balanceAfter
             << "| Time: " << t.timestamp << endl;
    }
}

// ================= CHANGE PIN =================
void UserMenu::changePin()
{
    cout<<"\n--------------------\n";
    cout<<"CHANGE PIN SECTION\n";
    cout<<"--------------------\n\n";
    string input;

    cout << "Enter current PIN: ";
    getline(cin, input);

    if (!isNumber(input) || stoi(input) != currentUser->pin)
    {
        cout << "Wrong PIN!\n";
        return;
    }

    string pin1, pin2;

    while (true)
    {
        cout << "Enter new PIN (4 digits): ";
        getline(cin, pin1);

        if (!isNumber(pin1) || pin1.length() != 4)
        {
            cout << "Invalid PIN!\n";
            continue;
        }

        cout << "Confirm new PIN: ";
        getline(cin, pin2);

        if (pin1 != pin2)
        {
            cout << "PINs do not match!\n";
            continue;
        }

        break;
    }

    int newPin = stoi(pin1);

    MYSQL* conn = DB::connect();
    string query = "UPDATE accounts SET pin = " + to_string(newPin) +
                   " WHERE account_id = '" + currentUser->accountId + "'";

    mysql_query(conn, query.c_str());
    mysql_close(conn);

    currentUser->pin = newPin;

    cout << "\nPIN changed successfully! Please login again with your new PIN.\n";
}