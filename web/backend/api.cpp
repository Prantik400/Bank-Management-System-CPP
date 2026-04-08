#include <iostream>
#include <string>
#include "../../data/DataManager.h"
#include "../../models/Transaction.h"
#include "../../database/db.h"

using namespace std;

int main(int argc, char* argv[])
{
    DataManager dm;

    if (argc < 2)
    {
        cout << "Invalid request";
        return 0;
    }

    string action = argv[1];

    if (action == "balance")
    {
        string id = argv[2];

        Account* acc = dm.findAccountById(id);

        if (acc)
        {
            cout << acc->balance;
            delete acc;
        }
        else
        {
            cout << "ERROR";
        }
    }

    return 0;
}