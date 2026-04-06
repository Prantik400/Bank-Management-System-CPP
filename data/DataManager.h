#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H


#include<vector>
#include"../models/Account.h"

class DataManager 
{
    private:
        
    public:
    //Crate new account
    void createAccount(const Account &acc);
    
    //Get all accounts
    std::vector<Account> getAllAccounts();

    //Find account by Id
    Account* findAccountById(string accountId);

    //Delete account 
    bool deleteAccount(string accountId);

    //Check if account exists
    bool accountExists(string accountId);

    //Get total bank balance
    double getTotalBankBalance();
};
#endif 