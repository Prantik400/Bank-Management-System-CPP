#include "Auth.h"
#include "../database/db.h"
#include <iostream>

using namespace std;

// ================= VERIFY PIN =================
bool verifyPin(const Account &acc, int enteredPin)
{
    return acc.pin == enteredPin;
}

// ================= LOGIN =================
Account* login(string accountId, int pin)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return nullptr;

    string query = "SELECT * FROM accounts WHERE account_id = '" +
                   accountId + "' AND pin = " + to_string(pin);

    if (mysql_query(conn, query.c_str()))
    {
        cout << "Login Error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return nullptr;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    if (result == NULL)
    {
        cout << "Error fetching result: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return nullptr;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == NULL)
    {
        // ❌ Don't print error here (handled in MainMenu)
        mysql_free_result(result);
        mysql_close(conn);
        return nullptr;
    }

    Account* acc = new Account();
    acc->accountId = row[0];
    acc->name = row[1];
    acc->balance = stod(row[2]);
    acc->pin = stoi(row[3]);

    mysql_free_result(result);
    mysql_close(conn);

    return acc;
}