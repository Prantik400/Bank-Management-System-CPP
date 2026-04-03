#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include<vector>
#include"../models/Account.h"

class DataManager 
{
    private:
        std::vector<Account> accounts;
    public:
    //Crate new account
    void createAccount(const Account &acc);
    
    //Get all accounts
    std::vector<Account>& getAllAccounts();

    //Find account by Id
    Account* findAccountById(int accountId);

    //Delete account 
    bool deleteAccount(int accountId);

    //Check if account exists
    bool accountExists(int accountId);

    //Get total bank balance
    double getTotalBankBalance();
};
#endif 