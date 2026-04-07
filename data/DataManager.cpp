#include <iostream>
#include "DataManager.h"
#include "../database/db.h"

using namespace std;

// ================= CREATE ACCOUNT =================
void DataManager::createAccount(const Account& acc)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return;

    string query = "INSERT INTO accounts VALUES('" +
                   acc.accountId + "', '" +
                   acc.name + "', " +
                   to_string(acc.balance) + ", " +
                   to_string(acc.pin) + ")";

    if (mysql_query(conn, query.c_str())) {
        cout << "Insert Error: " << mysql_error(conn) << endl;
    }

    mysql_close(conn);
}

// ================= GET ALL ACCOUNTS =================
vector<Account> DataManager::getAllAccounts()
{
    vector<Account> accounts;

    MYSQL* conn = DB::connect();
    if (conn == NULL) return accounts;

    string query = "SELECT * FROM accounts";

    if (mysql_query(conn, query.c_str())) {
        cout << "Fetch Error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return accounts;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        mysql_close(conn);
        return accounts;
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        Account acc;
        acc.accountId = row[0];
        acc.name = row[1];
        acc.balance = stod(row[2]);
        acc.pin = stoi(row[3]);

        accounts.push_back(acc);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return accounts;
}

// ================= FIND ACCOUNT =================
Account* DataManager::findAccountById(string accountId)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return nullptr;

    string query = "SELECT * FROM accounts WHERE account_id = '" + accountId + "'";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return nullptr;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        mysql_close(conn);
        return nullptr;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == NULL) {
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

// ================= DELETE ACCOUNT =================
bool DataManager::deleteAccount(string accountId)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return false;

    string query = "DELETE FROM accounts WHERE account_id = '" + accountId + "'";

    if (mysql_query(conn, query.c_str())) {
        cout << "Delete Error: " << mysql_error(conn) << endl;
        mysql_close(conn);   
        return false;
    }

    if (mysql_affected_rows(conn) == 0) {
        mysql_close(conn);
        return false;
    }

    mysql_close(conn);
    return true;
}

// ================= ACCOUNT EXISTS =================
bool DataManager::accountExists(string accountId)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return false;

    string query = "SELECT account_id FROM accounts WHERE account_id = '" + accountId + "'";

    if (mysql_query(conn, query.c_str())) {
        cout << "Check Error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return false;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        mysql_close(conn);
        return false;
    }

    bool exists = mysql_num_rows(result) > 0;

    mysql_free_result(result);
    mysql_close(conn);

    return exists;
}

// ================= TOTAL BALANCE =================
double DataManager::getTotalBankBalance()
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return 0;

    string query = "SELECT SUM(balance) FROM accounts";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 0;
    }

    MYSQL_RES* result = mysql_store_result(conn);

    if (result == NULL) {
        mysql_close(conn);
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    double total = 0;
    if (row[0] != NULL)
        total = stod(row[0]);

    mysql_free_result(result);
    mysql_close(conn);

    return total;
}

// ================= UPDATE BALANCE (STEP 2) =================
bool DataManager::updateBalance(string accountId, double newBalance)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return false;

    string query = "UPDATE accounts SET balance = " + to_string(newBalance) +
                   " WHERE account_id = '" + accountId + "'";

    if (mysql_query(conn, query.c_str())) {
        cout << "Update Balance Error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return false;
    }

    if(mysql_affected_rows(conn) == 0) {
        mysql_close(conn);
        return false;
    }
    mysql_close(conn);
    return true;
}

// ================= ADD TRANSACTION =================
bool DataManager::addTransaction(string accountId, string type, double amount, double balance)
{
    MYSQL* conn = DB::connect();
    if (conn == NULL) return false;

    string query = "INSERT INTO transactions(account_id, type, amount, balance) VALUES('" +
                   accountId + "', '" + type + "', " +
                   to_string(amount) + ", " +
                   to_string(balance) + ")";

    if (mysql_query(conn, query.c_str()))
    {
        cout << "Transaction Insert Error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return false;
    }

    mysql_close(conn);
    return true;
}

// ================= GET TRANSACTIONS =================
vector<Transaction> DataManager::getTransactions(string accountId)
{
    vector<Transaction> list;

    MYSQL* conn = DB::connect();
    if (conn == NULL) return list;

    string query = "SELECT type, amount, balance, timestamp FROM transactions WHERE account_id = '" + accountId + "' ORDER BY id ASC";

    if (mysql_query(conn, query.c_str()))
    {
        cout << "Error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return list;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL)
    {
        mysql_close(conn);
        return list;
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        Transaction t(
            row[0],                    // type
            stod(row[1]),              // amount
            stod(row[2]),              // balance
            row[3]                     // timestamp
        );

        list.push_back(t);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return list;
}