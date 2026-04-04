#ifndef UI_ADMIN_MENU_H
#define UI_ADMIN_MENU_H

#include "../data/DataManager.h"

class AdminMenu
{
private:
    DataManager& dataManager;

public:
    AdminMenu(DataManager& dm);
    void show();

    void createAccount();
    void deleteAccount();
    void viewAllAccounts();
    void viewTotalBalance();
};

#endif