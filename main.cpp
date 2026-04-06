#include <iostream>
#include "auth/Auth.h"
#include "ui/MainMenu.h"
#include "ui/UserMenu.h"
#include "ui/AdminMenu.h"


using namespace std;

int main()
{
    DataManager dataManager;

    dataManager.createAccount(acc1);

    MainMenu menu(dataManager);
    menu.show();

    return 0;
}