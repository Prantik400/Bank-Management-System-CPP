#include <iostream>
#include "../auth/Auth.h"
#include "MainMenu.h"
#include "UserMenu.h"

using namespace std;

MainMenu::MainMenu(DataManager& dm) : dataManager(dm) {}

void MainMenu::show()
{
    int choice;

    while (true)
    {
        cout << "\n===== BANK SYSTEM =====\n";
        cout << "1. Login\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id, pin;

            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter PIN: ";
            cin >> pin;

            Account* user = login(dataManager.getAllAccounts(), id, pin);

            if (user)
            {
                cout << "Login Successful!\n";

                UserMenu menu(dataManager, user);
                menu.show();   // 🔥 CONNECTED
            }
            else
            {
                cout << "Login Failed!\n";
            }

            break;
        }

        case 2:
            cout << "Exiting...\n";
            return;

        default:
            cout << "Invalid choice!\n";
        }
    }
}