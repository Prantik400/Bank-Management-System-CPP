#include "../utils//helpers.h"
#include <cctype>   // For isalnum
#include <iostream>
#include "AdminMenu.h"
#include <iostream>
#include <limits>   // For numeric_limits
using namespace std;

// Constructor
AdminMenu::AdminMenu(DataManager& dm) : dataManager(dm) {}

bool AdminMenu::verifyAdmin()
{
    string password;

    cout << "Enter Admin Password to confirm: ";
    cin >> password;
    if(password != "admin123") {
        cout << "Incorrect password! Access denied.\n";
        return false;
    }

    return true;
}

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
    string input;

    // Account ID (8 char alphanumeric + unique)
    while (true)
    {
    cout << "Enter Account ID (8 alphanumeric): ";
    cin >> input;

    if (input.length() != 8)
    {
        cout << " Must be exactly 8 characters!\n";
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
        cout << " Only letters and numbers allowed!\n";
        continue;
    }

    if (dataManager.accountExists(input))
    {
        cout << " ID already exists! Try another.\n";
        continue;
    }

    acc.accountId = input;
    break;
   }

    // Name
    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // FIX BUFFER
    getline(cin, input);

    if (input.empty() || !isValidName(input))
    {
        cout << "Invalid Name! Only letters and spaces allowed.\n";
        return;
    }

    acc.name = input;

    // Balance (supports decimal)
    cout << "Enter Initial Balance: ";
    cin >> input;

    if (!isDouble(input))
    {
        cout << "Invalid Balance! Only numeric values allowed.\n";
        return;
    }

    acc.balance = stod(input);

    if (acc.balance < 0)
    {
        cout << "Invalid Balance! Must be non-negative.\n";
        return;
    }

    // PIN (STRICT 4 DIGITS)
    string pin1, pin2;

    while (true)
   {
    cout << "Enter PIN (4 digits): ";
    cin >> pin1;

    if (!isNumber(pin1) || pin1.length() != 4)
    {
        cout << " PIN must be exactly 4 digits!\n";
        continue;
    }

    cout << "Confirm PIN: ";
    cin >> pin2;

    if (pin1 != pin2)
    {
        cout << " PINs do not match!\n";
        continue;
    }

    acc.pin = stoi(pin1);
    break;
    }

    // Admin Verification (FINAL STEP)
    if (!verifyAdmin())
    {
        cout << "Admin verification failed!\n";
        return;
    }

    //Create account
    dataManager.createAccount(acc);

    cout << "Account Created Successfully!\n";
}


// Delete an account
void AdminMenu::deleteAccount()
{
    string id;
    cout << "Enter Account ID to delete: ";
    cin >> id;

    if(id.empty()){
        cout << "Invalid Account ID!.\n";
        return;
    }

    if(!verifyAdmin()) {
        return;
    }

    if (dataManager.deleteAccount(id))
        cout << "Account deleted successfully!\n";
    else
        cout << "Account not found!\n";
}

// View all accounts
void AdminMenu::viewAllAccounts()
{
    if(!verifyAdmin()) {
        return;
    }

    auto accounts = dataManager.getAllAccounts();

    if (accounts.empty())
    {
        cout << "No accounts found!.\n";
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
    if(!verifyAdmin()) {
        return;
    }
    double total = dataManager.getTotalBankBalance();
    cout << "Total Bank Balance: Rs." << total << "\n";
}