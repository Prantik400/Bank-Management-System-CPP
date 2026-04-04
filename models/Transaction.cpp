#include "Transaction.h"

Transaction::Transaction(string t, double amt, double bal, string time)
{
    type = t;
    amount = amt;
    balanceAfter = bal;
    timestamp = time;
}