#include <iostream>
#include "auth/Auth.h"
#include "ui/MainMenu.h"
#include "ui/UserMenu.h"
#include "ui/AdminMenu.h"
#include "database/db.h"

using namespace std;

int main()
{
    DataManager dataManager;
    MYSQL* conn = DB::connect();
    if (conn != NULL) {
        cout << "\nDB Connected Successfully!\n";
        mysql_close(conn);
    }
    MainMenu menu(dataManager);
    menu.show();

    return 0;
}