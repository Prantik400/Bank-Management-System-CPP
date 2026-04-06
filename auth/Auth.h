#ifndef AUTH_H
#define AUTH_H

#include <vector>
#include "../models/Account.h"

bool verifyPin(const Account &acc, int enteredPin);
Account* login(string accountId, int enteredPin);

#endif