#include <iostream>
#include "../auth/Auth.h"
#include "MainMenu.h"
#include "UserMenu.h"
#include "AdminMenu.h"

using namespace std;

// Constructor
MainMenu::MainMenu(DataManager& dm) : dataManager(dm) {}

// Main Menu UI
void MainMenu::show()
{
    int choice;

    while (true)
    {
        cout << "\n===== BANK SYSTEM =====\n";
        cout << "1. User Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        // ================= USER LOGIN =================
        case 1:
        {
            int id, pin;

            cout << "Enter Account ID: ";
            cin >> id;

            cout << "Enter PIN: ";
            cin >> pin;

            Account* user = login(dataManager.getAllAccounts(), id, pin);

            if (user != nullptr)
            {
                cout << "Login Successful!\n";

                UserMenu userMenu(dataManager, user);
                userMenu.show();   //  Go to User Menu
            }
            else
            {
                cout << "Login Failed!\n";
            }

            break;
        }

        // ================= ADMIN LOGIN =================
        case 2:
        {
            string username, password;

            cout << "Enter Admin Username: ";
            cin >> username;

            cout << "Enter Admin Password: ";
            cin >> password;

            //  Simple Hardcoded Admin Check
            if (username == "admin" && password == "admin123")
            {
                cout << "Admin Login Successful!\n";

                AdminMenu adminMenu(dataManager);
                adminMenu.show();   //  Go to Admin Menu
            }
            else
            {
                cout << "Invalid Admin Credentials!\n";
            }

            break;
        }

        // ================= EXIT =================
        case 3:
            cout << "Exiting...\n";
            return;

        // ================= INVALID =================
        default:
            cout << "Invalid choice!\n";
        }
    }
}