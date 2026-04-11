#include <iostream>
#include "../auth/Auth.h"
#include "MainMenu.h"
#include "UserMenu.h"
#include "AdminMenu.h"
#include "../utils/helpers.h"

using namespace std;

// Constructor
MainMenu::MainMenu(DataManager& dm) : dataManager(dm) {}

// Main Menu UI
void MainMenu::show()
{
    string input;
    int choice;

    while (true)
    {
        cout << "\n===== BANK SYSTEM =====\n";
        cout << "\n1. User Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Exit\n";
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
        // ================= USER LOGIN =================
        case 1:
        {
            cout<<"\n--------------------\n";
            cout<<"USER LOGIN\n";
            cout<<"--------------------\n\n";
            string id, pinInput;
            cout << "Enter Account ID: ";
            getline(cin, id);
            id = trim(id);

            if (id.empty())
            {
                cout << "Account ID cannot be empty!\n";
                break;
            }

            cout << "Enter PIN: ";
            getline(cin, pinInput);
            pinInput = trim(pinInput);

            if (!isNumber(pinInput))
            {
                cout << "Invalid PIN!\n";
                break;
            }

            int pin = stoi(pinInput);

            Account* user = login(id, pin);

            if (user != nullptr)
            {
                cout << "\nLogin Successful!\n";

                UserMenu userMenu(dataManager, user);
                userMenu.show();
            }
            else
            {
                cout << "Invalid Account ID or PIN!\n";
            }

            break;
        }

        // ================= ADMIN LOGIN =================
        case 2:
        {
            cout<<"\n--------------------\n";
            cout<<"ADMIN LOGIN\n";
            cout<<"--------------------\n\n";
            string username, password;

            cout << "Enter Admin Username: ";
            getline(cin, username);
            username = trim(username);

            cout << "Enter Admin Password: ";
            getline(cin, password);
            password = trim(password);

            if (username == "admin" && password == "admin123")
            {
                cout << "Admin Login Successful!\n";

                AdminMenu adminMenu(dataManager);
                adminMenu.show();
            }
            else
            {
                cout << "Invalid Admin Credentials!\n";
            }

            break;
        }

        // ================= EXIT =================
        case 3:
            cout << "\nExiting...\n";
            return;

        default:
            cout << "Invalid choice!\n";
        }
    }
}