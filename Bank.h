#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Bank
{
    string BankName;
    long long AccountNumber;
    string AccountType;
    string TransactionId;
    string PinCode;
    double Balance;

public:
    Bank();
    Bank(string bankName, long long accountNumber, string accountType, string transactionId, string pinCode, double balance);
    Bank(string bankName, long long accountNumber, string accountType, string transactionId, string pinCode, double balance, int n);
    Bank(const Bank &b);
    string GetBankName() const;
    long long GetAccountNumber() const;
    string GetAccountType() const;
    string GetTransactionId() const;
    string GetPinCode() const;
    double GetBalance() const;
    bool IsValidAccount() const;
    void Deposit(double amount);
    bool Withdraw(double amount);
    void SetBalance(double amount);
    string GenerateTransactionID() const;
    void SaveAccountInfo() const;
    friend class BankManager;
};

#endif