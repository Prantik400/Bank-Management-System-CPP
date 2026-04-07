#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <vector>
#include <string>              
#include "../models/Account.h"
#include "../models/Transaction.h"

class DataManager 
{
public:
    // Create new account
    void createAccount(const Account &acc);
    
    // Get all accounts
    std::vector<Account> getAllAccounts();

    // Find account by ID
    Account* findAccountById(std::string accountId);

    // Delete account 
    bool deleteAccount(std::string accountId);

    // Check if account exists
    bool accountExists(std::string accountId);

    // Get total bank balance
    double getTotalBankBalance();

    // NEW balance update method
    bool updateBalance(std::string accountId, double newBalance);

    //Add transaction record
    bool addTransaction(std::string accountId, std::string type, double amount, double balance);

    // Get transaction history of user
    std::vector<Transaction> getTransactions(std::string accountId);
};

#endif