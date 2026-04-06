#include <iostream>
#include"DataManager.h"
#include"../database/db.h"
using namespace std;

//Create new account
void DataManager::createAccount(const Account& acc)
{
    MYSQL* conn = DB::connect();
if (conn == NULL) return;

string query = "INSERT INTO accounts VALUES(" +
               to_string(acc.accountId) + ", '" +
               acc.name + "', " +
               to_string(acc.balance) + ", " +
               to_string(acc.pin) + ")";

if(mysql_query(conn, query.c_str())) {
    cout << "Insert Error: " << mysql_error(conn) << endl;
}

mysql_close(conn);
}

//Get all accounts
std::vector<Account> DataManager::getAllAccounts()
{
    std::vector<Account> accounts;

    MYSQL* conn = DB::connect();
    if (conn == NULL) return accounts;

    string query = "SELECT * FROM accounts";

    if (mysql_query(conn, query.c_str())) {
        cout << "Fetch Error: " << mysql_error(conn) << endl;
        return accounts;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        Account acc;
        acc.accountId = stoi(row[0]);
        acc.name = row[1];
        acc.balance = stod(row[2]);
        acc.pin = stoi(row[3]);

        accounts.push_back(acc);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return accounts;
}


//Find account by Id
Account* DataManager::findAccountById(int accountId)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return nullptr;

    string query = "SELECT * FROM accounts WHERE account_id = " + to_string(accountId);

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        return nullptr;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == NULL) {
        mysql_free_result(result);
        mysql_close(conn);
        return nullptr;
    }

    Account* acc = new Account();
    acc->accountId = stoi(row[0]);
    acc->name = row[1];
    acc->balance = stod(row[2]);
    acc->pin = stoi(row[3]);

    mysql_free_result(result);
    mysql_close(conn);

    return acc;
}

//Delete accouunt
bool DataManager::deleteAccount(int accountId)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return false;

    string query = "DELETE FROM accounts WHERE account_id = " + to_string(accountId);

    if (mysql_query(conn, query.c_str())) {
        cout << "Delete Error: " << mysql_error(conn) << endl;
        return false;
    }

    mysql_close(conn);
    return true;
}

//Check if account exists
bool DataManager::accountExists(int accountId)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return false;

    string query = "SELECT account_id FROM accounts WHERE account_id = " + to_string(accountId);

    mysql_query(conn, query.c_str());
    MYSQL_RES* result = mysql_store_result(conn);

    bool exists = mysql_num_rows(result) > 0;

    mysql_free_result(result);
    mysql_close(conn);

    return exists;
}

//Get total bank balance
double DataManager::getTotalBankBalance()
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return 0;

    string query = "SELECT SUM(balance) FROM accounts";

    mysql_query(conn, query.c_str());
    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    double total = 0;
    if (row[0] != NULL)
        total = stod(row[0]);

    mysql_free_result(result);
    mysql_close(conn);

    return total;
}