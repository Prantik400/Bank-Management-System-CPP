#ifndef UI_MAIN_MENU_H
#define UI_MAIN_MENU_H

#include "../data/DataManager.h"

class MainMenu
{
private:
    DataManager& dataManager;

public:
    MainMenu(DataManager& dm);
    void show();
};

#endif