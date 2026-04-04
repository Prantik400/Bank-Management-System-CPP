#include <iomap>
#include <iostream>
#include "UserMenu.h"
#include "../core/AccountOperations.h"
#include "../models/Transaction.h"
#include "../utils/helpers.h"

using namespace std;

// Constructor
UserMenu::UserMenu(DataManager& dm, Account* user)
    : dataManager(dm), currentUser(user) {}

//  PIN Verification
bool UserMenu::verifyUserPin()
{
    int pin;
    cout << "Enter PIN: ";
    cin >> pin;

    if (pin != currentUser->pin)
    {
        cout << "Incorrect PIN!\n";
        return false;
    }

    return true;
}

// Menu
void UserMenu::show()
{
    int choice;

    while (true)
    {
        cout << "\n===== USER MENU =====\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. Transaction History\n";
        cout << "6. Change PIN\n";
        cout << "7. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: checkBalance(); break;
        case 2: deposit(); break;
        case 3: withdraw(); break;
        case 4: transfer(); break;
        case 5: showTransactionHistory(); break;
        case 6: changePin(); break;
        case 7:
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice!\n";
        }
    }
}

// Check Balance
void UserMenu::checkBalance()
{
    if (!verifyUserPin()) return;

    cout << "Balance: Rs." << currentUser->balance << endl;
}

// Deposit
void UserMenu::deposit()
{
    if (!verifyUserPin()) return;

    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount!\n";
        return;
    }

    currentUser->balance += amount;
    Transaction t("Deposited Rs.", amount, currentUser->balance, getCurrentTime());
    currentUser->addTransaction(t);

    cout << "Deposit successful!\n";
}

// Withdraw
void UserMenu::withdraw()
{
    if (!verifyUserPin()) return;

    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (!AccountOperations::withdraw(*currentUser, amount))
    {
        cout << "Withdrawal failed!\n";
        return;
    }

    if(amount <=0 || amount > currentUser->balance)
    {
        cout << "Invalid amount!\n";
        return;
    }

    Transaction t("Withdrew Rs.", amount, currentUser->balance, getCurrentTime());
    currentUser->addTransaction(t);
    cout << "Withdrawal successful!\n";
}

// Transfer
void UserMenu::transfer()
{
    if (!verifyUserPin()) return;

    int id;
    double amount;

    cout << "Enter receiver ID: ";
    cin >> id;

    Account* receiver = dataManager.findAccountById(id);

    if (!receiver)
    {
        cout << "User not found!\n";
        return;
    }

    cout << "Enter amount: ";
    cin >> amount;

    if (!AccountOperations::transfer(*currentUser, *receiver, amount))
    {
        cout << "Transfer failed!\n";
        return;
    }

    if(amount <=0 || amount > currentUser->balance)
    {
        cout << "Invalid amount!\n";
        return;
    }

    currentUser->balance -= amount;
    receiver->balance += amount;
    
    Transaction t1("Transferred Rs.", amount, currentUser->balance, getCurrentTime());
    Transaction t2("Received Rs.", amount, receiver->balance, getCurrentTime());
    currentUser->addTransaction(t1);
    receiver->addTransaction(t2);

    cout << "Transfer successful!\n";
}

//  Transaction History
void UserMenu::showTransactionHistory()
{
    if (!verifyUserPin()) return;

    if (currentUser->transactions.empty())
    {
        cout << "No transactions found!\n";
        return;
    }

    cout << "\n--- Transaction History ---\n";

    for (auto &t : currentUser->transactions)
    {
        cout << left << setw(18) << t.type 
             << "| Rs." << setw(6) << t.amount 
             << "| Balance: Rs." << setw(8) << t.balanceAfter 
             << "|Time: " << t.timestamp << endl;
    }
}

//  Change PIN
void UserMenu::changePin()
{
    int oldPin, newPin;

    cout << "Enter current PIN: ";
    cin >> oldPin;

    if (oldPin != currentUser->pin)
    {
        cout << "Wrong PIN!\n";
        return;
    }

    cout << "Enter new PIN: ";
    cin >> newPin;

    currentUser->pin = newPin;
    cout << "PIN changed successfully!\n";
}