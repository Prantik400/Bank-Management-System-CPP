#include "AdminMenu.h"
#include <iostream>
using namespace std;

// Constructor
AdminMenu::AdminMenu(DataManager& dm) : dataManager(dm) {}

// Show Admin Menu
void AdminMenu::show()
{
    int choice;

    while (true)
    {
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. Create Account\n";
        cout << "2. Delete Account\n";
        cout << "3. View All Accounts\n";
        cout << "4. View Total Bank Balance\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            deleteAccount();
            break;
        case 3:
            viewAllAccounts();
            break;
        case 4:
            viewTotalBalance();
            break;
        case 5:
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice!\n";
        }
    }
}

// Create a new account
void AdminMenu::createAccount()
{
    Account acc;

    cout << "Enter Account ID: ";
    cin >> acc.accountId;

    cout << "Enter Name: ";
    cin >> acc.name;

    cout << "Enter Initial Balance: ";
    cin >> acc.balance;

    cout << "Set PIN: ";
    cin >> acc.pin;

    dataManager.createAccount(acc);

    cout << "Account Created Successfully!\n";
}

// Delete an account
void AdminMenu::deleteAccount()
{
    int id;
    cout << "Enter Account ID to delete: ";
    cin >> id;

    if (dataManager.deleteAccount(id))
        cout << "Account deleted successfully!\n";
    else
        cout << "Account not found!\n";
}

// View all accounts
void AdminMenu::viewAllAccounts()
{
    auto& accounts = dataManager.getAllAccounts();

    if (accounts.empty())
    {
        cout << "No accounts found.\n";
        return;
    }

    cout << "\n--- All Accounts ---\n";
    for (const auto& acc : accounts)
    {
        cout << "ID: " << acc.accountId
             << " | Name: " << acc.name
             << " | Balance: " << acc.balance << "\n";
    }
}

// View total bank balance
void AdminMenu::viewTotalBalance()
{
    double total = dataManager.getTotalBankBalance();
    cout << "Total Bank Balance: Rs." << total << "\n";
}