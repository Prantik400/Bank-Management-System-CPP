#include <iostream>
#include "data/DataManager.h"
#include "ui/MainMenu.h"

using namespace std;

int main()
{
    // Create Data Manager
    DataManager dataManager;

    // 🔥 Add dummy account (for testing)
    Account acc1;
    acc1.accountId = 1;
    acc1.name = "Prantik";
    acc1.balance = 1000.0;
    acc1.pin = 1234;

    dataManager.createAccount(acc1);

    // Start Main Menu
    MainMenu menu(dataManager);
    menu.show();

    return 0;
}