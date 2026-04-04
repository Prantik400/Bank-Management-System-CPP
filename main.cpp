#include <iostream>
#include "auth/Auth.h"
#include "ui/MainMenu.h"
#include "ui/UserMenu.h"
#include "ui/AdminMenu.h"


using namespace std;

int main()
{
    DataManager dataManager;

    // dummy account
    Account acc1;
    acc1.accountId = 1;
    acc1.name = "Prantik";
    acc1.balance = 1000;
    acc1.pin = 1234;

    dataManager.createAccount(acc1);

    MainMenu menu(dataManager);
    menu.show();

    return 0;
}