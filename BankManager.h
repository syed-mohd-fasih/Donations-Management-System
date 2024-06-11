#ifndef BANKMANAGER_H
#define BANKMANAGER_H

#include "Bank.h"
#include "User.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;

class BankManager
{
public:
    static void TransferMoney(User &x, long long y, double amount);
    static void UpdateAccountInfo(const Bank &account);
    static bool AccountExists(long long accountNumber);
};

#endif