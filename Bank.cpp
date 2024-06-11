#include "Bank.h"

using namespace std;

Bank::Bank() : BankName("NaN"), AccountNumber(0000000), AccountType("NaN"), TransactionId(GenerateTransactionID()), PinCode("1234"), Balance(0.0) {}
Bank::Bank(string bankName, long long accountNumber, string accountType, string transactionId, string pinCode, double balance) 
    : BankName(bankName), AccountNumber(accountNumber), AccountType(accountType), 
    TransactionId(transactionId.empty() ? GenerateTransactionID() : transactionId), PinCode(pinCode), Balance(balance) { SaveAccountInfo(); }
Bank::Bank(string bankName, long long accountNumber, string accountType, string transactionId, string pinCode, double balance, int n) 
    : BankName(bankName), AccountNumber(accountNumber), AccountType(accountType), 
    TransactionId(transactionId.empty() ? GenerateTransactionID() : transactionId), PinCode(pinCode), Balance(balance) {}
Bank::Bank(const Bank &b)
{
    this->BankName = b.BankName;
    this->AccountNumber = b.AccountNumber;
    this->AccountType = b.AccountType;
    this->TransactionId = b.TransactionId;
    this->PinCode = b.PinCode;
    this->Balance = b.Balance;
}
void Bank::SaveAccountInfo() const
{
    ofstream outputFile("account_data.txt", ios::app);
    if (outputFile.is_open())
    {
        outputFile << AccountNumber << "," << BankName << "," << AccountType << "," << TransactionId << "," << PinCode << "," << fixed << setprecision(2) << Balance << "," << endl;
        outputFile << "***********" << endl;
        outputFile.close();
    } else {
        cout << "\n\n\nSystem Error: Unable to open file for account information update.\n\n\n"
             << endl;
    }
}
string Bank::GetBankName() const
{
    return BankName;
}
long long Bank::GetAccountNumber() const
{
    return AccountNumber;
}
string Bank::GetAccountType() const
{
    return AccountType;
}
string Bank::GetTransactionId() const
{
    return TransactionId;
}
string Bank::GetPinCode() const
{
    return PinCode;
}
double Bank::GetBalance() const
{
    return Balance;
}
bool Bank::IsValidAccount() const
{
    ifstream inputFile("account_data.txt");
    string line;
    while (getline(inputFile, line))
    {
        if (line == to_string(AccountNumber))
        {
            getline(inputFile, line);
            if (line == PinCode)
            {
                inputFile.close();
                return true;
            }
        }
    }
    inputFile.close();
    return false;
}
string Bank::GenerateTransactionID() const
{
    srand(time(0));
    long long transactionNumber = rand() % 1000000;
    string transactionId = "TXN" + to_string(transactionNumber);
    return transactionId;
}
void Bank::Deposit(double amount)
{
    Balance += amount;
}
bool Bank::Withdraw(double amount)
{
    if (Balance >= amount)
    {
        Balance -= amount;
        return true;
    }
    return false;
}
void Bank::SetBalance(double amount)
{
    Balance += amount;
}
