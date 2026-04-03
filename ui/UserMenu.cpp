#include <iostream>
#include "UserMenu.h"
#include "../core/AccountOperations.h"

using namespace std;

// Constructor
UserMenu::UserMenu(DataManager& dm, Account* user)
    : dataManager(dm), currentUser(user) {}

// 🔥 PIN Verification
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

// ✅ Check Balance
void UserMenu::checkBalance()
{
    if (!verifyUserPin()) return;

    cout << "Balance: ₹" << currentUser->balance << endl;
}

// ✅ Deposit
void UserMenu::deposit()
{
    if (!verifyUserPin()) return;

    double amount;
    cout << "Enter amount: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount!\n";
        return;
    }

    currentUser->balance += amount;
    currentUser->addTransaction("Deposited ₹" + to_string(amount));

    cout << "Deposit successful!\n";
}

// ✅ Withdraw
void UserMenu::withdraw()
{
    if (!verifyUserPin()) return;

    double amount;
    cout << "Enter amount: ";
    cin >> amount;

    if (!AccountOperations::withdraw(*currentUser, amount))
    {
        cout << "Withdrawal failed!\n";
        return;
    }

    currentUser->addTransaction("Withdrew ₹" + to_string(amount));
    cout << "Withdrawal successful!\n";
}

// ✅ Transfer
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

    currentUser->addTransaction("Transferred ₹" + to_string(amount) + " to ID " + to_string(id));
    receiver->addTransaction("Received ₹" + to_string(amount));

    cout << "Transfer successful!\n";
}

// ✅ Transaction History
void UserMenu::showTransactionHistory()
{
    if (!verifyUserPin()) return;

    if (currentUser->transactionHistory.empty())
    {
        cout << "No transactions.\n";
        return;
    }

    cout << "\n--- Transaction History ---\n";

    for (auto &t : currentUser->transactionHistory)
    {
        cout << t << endl;
    }
}

// ✅ Change PIN
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