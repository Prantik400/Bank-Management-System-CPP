#include"DataManager.h"

//Create new account
void DataManager::createAccount(const Account& acc)
{
    if(accountExists(acc.accountId))
      return;
    accounts.push_back(acc);
}

//Get all accounts
std::vector<Account>& DataManager::getAllAccounts() 
{
    return accounts;
}

//Find account by Id
Account* DataManager::findAccountById(int accountId) 
{
    for (auto& acc : accounts) 
    {
        if (acc.accountId == accountId) 
        {
            return &acc;
        }
    }
    return nullptr; // Not found
}

//Delete accouunt
bool DataManager::deleteAccount(int accountId) 
{
    for (auto it = accounts.begin(); it != accounts.end(); ++it) 
    {
        if (it->accountId == accountId) 
        {
            accounts.erase(it);
            return true; // Deleted successfully
        }
    }
    return false; // Not found
}

//Check if account exists
bool DataManager::accountExists(int accountId) 
{
    return findAccountById(accountId) != nullptr;
}

//Get total bank balance
double DataManager::getTotalBankBalance() 
{
    double total = 0.0;
    for (const auto& acc : accounts) 
    {
        total += acc.balance;
    }
    return total;
}