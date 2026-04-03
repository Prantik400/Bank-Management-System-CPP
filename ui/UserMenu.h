#ifndef UI_USER_MENU_H
#define UI_USER_MENU_H

#include "../data/DataManager.h"
#include "../models/Account.h"

class UserMenu
{
private:
    DataManager& dataManager;
    Account* currentUser;

    bool verifyUserPin();
public:
    UserMenu(DataManager& dm, Account* user);

    void show();

    void checkBalance();
    void deposit();
    void withdraw();
    void transfer();
    void showTransactionHistory();
    void changePin();
};

#endif