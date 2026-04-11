#include "../utils/helpers.h"
#include <cctype>
#include "AdminMenu.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor
AdminMenu::AdminMenu(DataManager& dm) : dataManager(dm) {}

bool AdminMenu::verifyAdmin()
{
    string password;

    cout << "\nEnter Admin Password to confirm: ";
    getline(cin, password);
    password = trim(password);

    if (password != "admin123")
    {
        cout << "Incorrect password! Access denied.\n";
        return false;
    }

    return true;
}

// Show Admin Menu
void AdminMenu::show()
{
    string input;
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
        case 1: createAccount(); break;
        case 2: deleteAccount(); break;
        case 3: viewAllAccounts(); break;
        case 4: viewTotalBalance(); break;
        case 5:
            cout << "\nLogging out...\n";
            return;
        default:
            cout << "Invalid choice!\n";
        }
    }
}

// Create Account
void AdminMenu::createAccount()
{
    cout<<"\n--------------------\n";
    cout<<"CREATE ACCOUNT\n";
    cout<<"--------------------\n\n";
    Account acc;
    string input;

    // Account ID
    while (true)
    {
        cout << "\nEnter Account ID (8 alphanumeric): ";
        getline(cin, input);
        input = trim(input);

        if (input.length() != 8)
        {
            cout << "Must be exactly 8 characters!\n";
            continue;
        }

        bool valid = true;
        for (char c : input)
        {
            if (!isalnum(c))
            {
                valid = false;
                break;
            }
        }

        if (!valid)
        {
            cout << "Only letters and numbers allowed!\n";
            continue;
        }

        if (dataManager.accountExists(input))
        {
            cout << "ID already exists! Try another.\n";
            continue;
        }

        acc.accountId = input;
        break;
    }

    // Name
    while (true)
    {
        cout << "Enter Name: ";
        getline(cin, input);
        input = trim(input);

        if (input.empty())
        {
            cout << "Name cannot be empty!\n";
            continue;
        }

        if (!isValidName(input))
        {
            cout << "Only letters and spaces allowed!\n";
            continue;
        }

        acc.name = input;
        break;
    }

    // Balance
    while (true)
    {
        cout << "Enter Initial Balance: ";
        getline(cin, input);
        input = trim(input);

        if (!isDouble(input))
        {
            cout << "Invalid Balance!\n";
            continue;
        }

        acc.balance = stod(input);

        if (acc.balance < 0)
        {
            cout << "Balance must be non-negative!\n";
            continue;
        }

        break;
    }

    // PIN
    string pin1, pin2;
    while (true)
    {
        cout << "Enter PIN (4 digits): ";
        getline(cin, pin1);

        if (!isNumber(pin1) || pin1.length() != 4)
        {
            cout << "PIN must be exactly 4 digits!\n";
            continue;
        }

        cout << "Confirm PIN: ";
        getline(cin, pin2);

        if (pin1 != pin2)
        {
            cout << "PINs do not match!\n";
            continue;
        }

        acc.pin = stoi(pin1);
        break;
    }

    if (!verifyAdmin())
    {
        cout << "Admin verification failed!\n";
        return;
    }

    dataManager.createAccount(acc);

    // Initial transaction
    dataManager.addTransaction(
        acc.accountId,
        "Account Created by Admin (System)",
        acc.balance,
        acc.balance
    );

    cout << "\nAccount Created Successfully!\n";
}

// Delete Account
void AdminMenu::deleteAccount()
{
    cout<<"\n--------------------\n";
    cout<<"DELETE ACCOUNT\n";
    cout<<"--------------------\n\n";
    string id;
    cout << "\nEnter Account ID to delete: ";
    getline(cin, id);
    id = trim(id);

    if (id.length() != 8)
    {
        cout << "Invalid Account ID!\n";
        return;
    }

    if (!verifyAdmin()) return;

    if (dataManager.deleteAccount(id))
        cout << "\nAccount deleted successfully!\n";
    else
        cout << "Account not found!\n";
}

// View Accounts
void AdminMenu::viewAllAccounts()
{
    cout<<"\n--------------------\n";
    cout<<"ALL ACCOUNT DASHBOARD\n";
    cout<<"--------------------\n\n";
    if (!verifyAdmin()) return;

    auto accounts = dataManager.getAllAccounts();

    if (accounts.empty())
    {
        cout << "No accounts found!\n";
        return;
    }

    cout << "\n-------------------------- All Accounts --------------------------\n\n";
    for (const auto& acc : accounts)
    {
        cout <<left << setw(10) << "ID: " << acc.accountId
             << " | Name: " << setw(20) << acc.name
             << " | Balance: " << setw(12) << acc.balance << "\n";
    }
}

// Total Balance
void AdminMenu::viewTotalBalance()
{
    cout<<"\n--------------------\n";
    cout<<"TOTAL BALANCE OF BANK\n";
    cout<<"--------------------\n\n";
    if (!verifyAdmin()) return;

    double total = dataManager.getTotalBankBalance();
    cout << "\nTotal Bank Balance: Rs." << total << "\n";
}