#include "BankManager.h"

using namespace std;

void BankManager::TransferMoney(User &x, long long y, double amount)
{
    char ch;
    string accNum, bankName, accountType, transactionId, pinCode, bal, line;
    if (x.bankAccount.GetBalance() >= amount)
    {
        x.setBalance(-amount);
        ifstream inputFile("account_data.txt");
        ofstream tempFile("temp_data.txt");
        if (inputFile.is_open() && tempFile.is_open())
        {
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                getline(ss, accNum, ',');
                string accountNumber = accNum;
                getline(ss, bankName, ',');
                getline(ss, accountType, ',');
                getline(ss, transactionId, ',');
                getline(ss, pinCode, ',');
                getline(ss, bal, ',');
                getline(inputFile, line);
                if (accountNumber == to_string(x.bankAccount.GetAccountNumber()))
                {
                    tempFile << x.bankAccount.GetAccountNumber() << "," << x.bankAccount.GetBankName() << "," << x.bankAccount.GetAccountType() << "," << x.bankAccount.GenerateTransactionID() << "," << x.bankAccount.GetPinCode() << "," << x.bankAccount.GetBalance() << "," << endl;
                    tempFile << "***********" << endl;
                }
                else if (accountNumber == to_string(y))
                {
                    tempFile << accountNumber << "," << bankName << "," << accountType << "," << transactionId << "," << pinCode << "," << (stod(bal) + amount) << "," << endl;
                    tempFile << "***********" << endl;
                    cout << "\nTransfer Successful!\n";
                    ch = _getch();
                } else {
                    tempFile << accountNumber << "," << bankName << "," << accountType << "," << transactionId << "," << pinCode << "," << bal << "," << endl;
                    tempFile << "***********" << endl;
                }
            }
            inputFile.close();
            tempFile.close();
            remove("account_data.txt");
            rename("temp_data.txt", "account_data.txt");
        } else {
            cout << "\n\n\nSystem Error: Unable to open file for account information update.\n\n\n"
                 << endl;
            ch = _getch();
        }
    } else {
        cout << "\n\n\nSystem Message: Entered Amount is Greater Than Bank Balance.\n\n\n"
             << endl;
        ch = _getch();
    }
}
bool BankManager::AccountExists(long long accountNumber)
{
    ifstream inputFile("account_data.txt");
    string line;
    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            getline(ss, line, ',');
            if (line == to_string(accountNumber))
            {
                inputFile.close();
                return true;
            }
            getline(inputFile, line);
        }
        inputFile.close();
    }
    return false;
}
