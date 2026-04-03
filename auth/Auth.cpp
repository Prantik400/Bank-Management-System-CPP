#include "Auth.h"

bool verifyPin(const Account &acc, int enteredPin)
{
    return acc.pin == enteredPin;
}

Account* login(std::vector<Account> &accounts, int accountId, int enteredPin)
{
    for (auto &acc : accounts)
    {
        if (acc.accountId == accountId)
        {
            
            if (verifyPin(acc, enteredPin))
            {
                return &acc; // Successful login
            }
            else 
            {
                return nullptr; // wrong pin
            }
        }
    }
    return nullptr;
}