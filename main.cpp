#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
using namespace std;
double XX;
void header();
void load();
string onlyTakeInteger(string x)
{
    string num;
    string temp;
    char ch;
    int y = 0;
    do
    {
        ch = _getch();
        temp = ch;
        if (ch > 47 && ch < 58)
        {
            num = num + temp;
            cout << "\r" << x << num;
            ++y;
        }
        if (ch == 8)
        {
            temp = num.substr(0, y - 1);
            num = temp;
            if (y != 0)
                --y;
            cout << "\r" << x << num << " ";
            cout << "\r" << x << num;
        }
        if (ch == 13)
            break;
    } while (1);
    return num;
}
string onlyTakeAlphabate(string x)
{
    string num;
    string temp;
    char ch;
    int y = 0;
    cout << x;
    do
    {
        ch = _getch();
        temp = ch;
        if (ch > 65 && ch <= 90 || ch >= 97 && ch <= 122 || ch == 32)
        {
            num = num + temp;
            cout << "\r" << x << num;
            ++y;
        }
        if (ch == 8)
        {
            temp = num.substr(0, y - 1);
            num = temp;
            if (y != 0)
                --y;
            system("cls");
            cout << "\r" << x << num << " ";
            cout << "\r" << x << num;
        }
        if (ch == 13)
            break;
    } while (1);
    return num;
}
string generateID()
{
    struct tm timee;
    time_t now = time(0);
    errno_t err = localtime_s(&timee, &now);
    if (err == 0)
        cout << "\nSuccess\n";
    else
        cout << "\nError\n";
    int year = 1900 + timee.tm_year;
    int month = timee.tm_mon + 1;
    int hour = timee.tm_hour;
    int minute = timee.tm_min;
    char id[12];
    int index = 0;
    id[index++] = '0' + year / 10 % 10;
    id[index++] = '0' + year % 10;
    id[index++] = '-';
    id[index++] = '0' + hour / 10;
    id[index++] = '0' + hour % 10;
    id[index++] = '0' + minute / 10;
    id[index++] = '0' + minute % 10;
    id[index] = '\0';
    return string(id);
}
class BankManager;
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
Bank::Bank() : BankName("NaN"), AccountNumber(0000000), AccountType("NaN"), TransactionId(GenerateTransactionID()), PinCode("1234"), Balance(0.0) {}
Bank::Bank(string bankName, long long accountNumber, string accountType, string transactionId, string pinCode, double balance) : BankName(bankName), AccountNumber(accountNumber), AccountType(accountType), TransactionId(transactionId.empty() ? GenerateTransactionID() : transactionId), PinCode(pinCode), Balance(balance) { SaveAccountInfo(); }
Bank::Bank(string bankName, long long accountNumber, string accountType, string transactionId, string pinCode, double balance, int n) : BankName(bankName), AccountNumber(accountNumber), AccountType(accountType), TransactionId(transactionId.empty() ? GenerateTransactionID() : transactionId), PinCode(pinCode), Balance(balance) {}
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
    }
    else
    {
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
class User
{
protected:
    string userId;
    string username;
    string email;
    string password;
    Bank bankAccount;

public:
    User() : username("NaN"), email("NaN"), password("NaN"), userId("NaN"), bankAccount(*(new Bank())) {}
    User(string Username, string Email, string pass, Bank &account, string Id = generateID()) : bankAccount(account)
    {
        if (isEmailExist(Email))
        {
            while (isEmailExist(Email))
            {
                cout << "Error: Email already exists! Please try again with a different email." << endl;
                cout << "\nEnter new email: ";
                cin >> Email;
            }
            cout << "Enter your username: ";
            cin >> Username;
            cout << "Enter your password: ";
            cin >> pass;
        }
        this->username = Username;
        this->email = Email;
        while (1)
        {
            if (isPasswordValid(pass))
            {
                this->password = encryptPassword(pass);
                break;
            }
            else
            {
                cout << "Invalid Password! Re-Enter password: " << endl;
                cout << "Enter Password here: " << endl;
                cin >> pass;
            }
        }
        if (isIDExist(Id))
        {
            while (isIDExist(Id))
            {
                int n = stoi(Id.substr(4, 4)) + 1;
                string m = to_string(n);
                if (n < 1000)
                {
                    m = Id.substr(0, 4) + "0" + m;
                }

                Id = m;
            }
        }
        this->userId = Id;
        saveToFile();
    }
    User(string username, string email, string pass, Bank &account, string Id, int n) : bankAccount(account)
    {
        this->username = username;
        this->email = email;
        this->password = pass;
        this->userId = Id;
    }
    double currentBalance()
    {
        return bankAccount.GetBalance();
    }
    void setBalance(double bal)
    {
        bankAccount.SetBalance(bal);
    }
    bool validateEmail(string email)
    {
        string Email;
        int x;
        for (int i = 0; i < email.length(); i++)
        {
            if (email[i] == '@')
            {
                Email = email.substr(i, email.length() - i);
                break;
            }
        }
        if (Email == "@gmail.com")
        {
            return false;
        }
        return true;
    }
    bool isPasswordValid(string password)
    {
        bool hasSpecialChar = false;
        bool hasUpperCase = false;
        bool hasLowerCase = false;
        bool hasNumber = false;
        for (int i = 0; i < password.size(); i++)
        {
            char c = password[i];
            if (c >= 'a' && c <= 'z')
            {
                hasLowerCase = true;
            }
            else if (c >= 'A' && c <= 'Z')
            {
                hasUpperCase = true;
            }
            else if (c >= '0' && c <= '9')
            {
                hasNumber = true;
            }
            else
            {
                hasSpecialChar = true;
            }
        }
        if (!hasSpecialChar)
        {
            cout << "\nYour password must contain at least one special character.\n";
        }
        if (!hasUpperCase)
        {
            cout << "\nYour password must contain at least one uppercase letter.\n";
        }
        if (!hasLowerCase)
        {
            cout << "\nYour password must contain at least one lowercase letter.\n";
        }
        if (!hasNumber)
        {
            cout << "\nYour password must contain at least one numeric character.\n";
        }
        if (password.size() < 6)
        {
            cout << "\nYour password must be at least 6 characters long.\n";
        }
        return hasSpecialChar && hasUpperCase && hasLowerCase && hasNumber && password.size() >= 6;
    }
    string encryptPassword(string x)
    {
        int size = 0, Mode;
        char Mark;
        for (int i = 0; i < x.size(); i++)
        {
            size += x[i];
        }
        Mark = x[0];
        Mode = size % 25;
        if (x[0] >= 97)
        {
            x[0] -= Mode;
        }
        else
        {
            x[0] += Mode;
        }
        for (int i = 1; i < x.size(); i++)
        {
            if (i % 2 == 0)
            {
                x[i] += 2;
            }
            else
            {
                x[i] -= 2;
            }
        }
        x = x + Mark;
        return x;
    }
    string getUsername() const
    {
        return username;
    }
    string getEmail() const
    {
        return email;
    }
    string getPassword() const
    {
        return password;
    }
    string getuserId()
    {
        return userId;
    }
    void setPassword(string currentPassword)
    {
        string newPassword;
        currentPassword = encryptPassword(currentPassword);
        if (password == currentPassword)
        {
            cout << "\n\t\t\tEnter your new password: ";
            cin >> newPassword;
            password = encryptPassword(newPassword);
            updateFile();
            cout << "\n\n\nSystem Message: Password updated successfully!\n\n\n"
                 << endl;
        }
        else
        {
            cout << "\n\n\nSystem Error: Incorrect current password!\n\n\n"
                 << endl;
        }
    }
    void setUsername()
    {
        string name;
        cout << "\n\t\t\tEnter your new Username: ";
        cin >> username;
        updateFile();
        cout << "\n\n\nSystem Messge: Username updated successfully!\n\n\n"
             << endl;
    }
    void saveToFile() const
    {
        ofstream fout("users.txt", ios::app);
        if (fout.is_open())
        {
            fout << email << "," << username << "," << password << "," << userId << "," << endl;
            fout.close();
        }
        else
        {
            cout << "\n\n\nSystem Error: Could not open file for writing!\n\n\n"
                 << endl;
        }
    }
    void saveForAcceptor() const
    {
        ofstream fout("Acceptor.txt", ios::app);
        if (fout.is_open())
        {
            fout << email << "," << userId << "," << bankAccount.GetAccountNumber() << "," << endl;
            fout.close();
        }
        else
        {
            cout << "\n\n\nSystem Error: Could not open file for writing!\n\n\n"
                 << endl;
        }
    }
    void updateFile() const
    {
        ifstream fin("users.txt");
        ofstream fout("temp.txt");
        string line;
        while (getline(fin, line))
        {
            string storedEmail = line.substr(0, line.find(","));
            if (storedEmail == email)
            {
                fout << email << "," << username << "," << password << "," << userId << "," << endl;
            }
            else
            {
                fout << line << endl;
            }
        }
        fin.close();
        fout.close();
        remove("users.txt");
        if (!rename("temp.txt", "users.txt"))
            cout << "\n\n\nSystem Message: File Update Success\n\n\n";
        else
            cout << "\n\n\nSystem Message: File Update Failed\n\n\n";
    }
    static User findUserByEmailORId(string emailORId)
    {
        ifstream fin("users.txt");
        ifstream ft("account_data.txt");
        string line, line1;
        while (getline(fin, line) && getline(ft, line1))
        {
            string storedEmail, username, pass, Id, Bname, AccType, Tid;
            string accNum;
            string pincode;
            string balance;
            stringstream ss(line);
            stringstream ss1(line1);
            getline(ss, storedEmail, ',');
            getline(ss, username, ',');
            getline(ss, pass, ',');
            getline(ss, Id, ',');
            getline(ss1, accNum, ',');
            getline(ss1, Bname, ',');
            getline(ss1, AccType, ',');
            getline(ss1, Tid, ',');
            getline(ss1, pincode, ',');
            getline(ss1, balance, ',');
            if (storedEmail == emailORId || Id == emailORId)
            {
                Bank bank(Bname, stoll(accNum), AccType, Tid, pincode, stod(balance), 1);

                return User(username, storedEmail, pass, bank, Id, 1);
            }
        }
        ft.close();
        fin.close();
        return User();
    }
    static bool isEmailExist(string email)
    {
        ifstream fin("users.txt");
        string line;
        while (getline(fin, line))
        {
            string storedEmail = line.substr(0, line.find(","));
            if (storedEmail == email)
            {
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }
    static bool isIDExist(string Id)
    {
        ifstream fin("users.txt");
        string line;
        while (getline(fin, line))
        {
            string storedId;
            stringstream ss(line);
            getline(ss, storedId, ',');
            getline(ss, storedId, ',');
            getline(ss, storedId, ',');
            getline(ss, storedId, ',');
            if (storedId == Id)
            {
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }
    void virtual signup()
    {
        string email, password, username;
        cout << "\nEnter your email: ";
        cin >> email;
        if (isEmailExist(email))
        {
            cout << "Error: Email already exists! Please try again with a different email." << endl;
        }
        else
        {
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;
            Bank tempBank(" ", 000000000, " ", " ", " ", 0.0, 1);
            User newUser(username, email, password, tempBank);
            newUser.saveToFile();
            cout << "Your user-ID is: " << newUser.getuserId() << endl;
            cout << "Sign up successful!" << endl;
        }
    }
    void virtual login()
    {
        string email, password, username, currentPassword, newPassword, emailORId;
        string choice;
        int choice1 = 0;
        cout << "\nEnter your email or UserID: ";
        cin >> emailORId;
        cout << "Enter your password: ";
        cin >> password;
        User user = User::findUserByEmailORId(emailORId);
        if (user.getEmail() == "NaN")
        {
            cout << "Error: User not found! Please try again with a valid email." << endl;
        }
        else
        {
            if (user.getPassword() == user.encryptPassword(password))
            {
                cout << "\nLogin successful!" << endl;
                do
                {
                    cout << "\n---------------------" << endl;
                    cout << "1. Change password" << endl;
                    cout << "2. Logout" << endl;
                    cout << "---------------------" << endl;
                    cout << "Enter your choice (1-2): ";
                    choice = onlyTakeInteger("Enter your choice (1-2): ");
                    choice1 = stoi(choice);
                    switch (choice1)
                    {
                    case 1:
                        cout << "\nEnter your current password: ";
                        cin >> currentPassword;
                        user.setPassword(currentPassword);
                        break;
                    case 2:
                        cout << "\nLogout successful!" << endl;
                        break;
                    default:
                        cout << "Invalid choice! Please try again." << endl;
                        break;
                    }
                } while (choice1 != 2);
            }
            else
            {
                cout << "Error: Incorrect password! Please try again." << endl;
            }
        }
    }
    friend class BankManager;
};

class Acceptor : public User
{
    int acceptorId;
    string message;

public:
    Acceptor() : User()
    {
        acceptorId = 0;
    }
    Acceptor(string name, string email, string password, Bank &account, string Id = "A" + generateID()) : User(name, email, password, account, Id)
    {
        this->acceptorId = 0;
        message = "NaN";
    }
    Acceptor(string username, string email, string pass, Bank &account, string Id, int n) : User(username, email, pass, account, Id, n)
    {
        acceptorId = 0;
        message = "NaN";
    }
    void signup()
    {
        char ch;
        string email, password, username;
        cout << "\n\t\t\tEnter your email: ";
        do
        {
            int c = 0;
            cin >> email;
            if (validateEmail(email))
            {
                cout << "\n\t\t\tInvalid Email format!\n\n\t\t\tPlease enter email with valid format: " << endl;
                c = -1;
            }
        } while (validateEmail(email));
        if (isEmailExist(email))
        {
            cout << "\n\n\nSystem Error: Email already exists! Please try again with a different email.\n\n\n"
                 << endl;
        }
        else
        {
            char BankName[20];
            char accType[20];
            long long aNum;
            int pinCode;
            cout << "\n\t\t\tEnter your username: ";
            cin >> username;
            cout << "\n\t\t\tEnter your password: ";
            cin >> password;
            cout << "\n\t\t\tEnter your bank name:  ";
            cin >> ws;
            cin.getline(BankName, 19);
            cout << "\n\t\t\tEnter your Account Number: ";
            cin >> aNum;
            cout << "\n\t\t\tEnter account type:";
            cin >> ws;
            cin >> accType;
            cout << "\n\t\t\tEnter your PinCode: ";
            cin >> pinCode;
            Bank tempBank(string(BankName), aNum, string(accType), "1234456", to_string(pinCode), 0.0);
            Acceptor newUser(username, email, password, tempBank);
            newUser.saveToFile();
            newUser.saveForAcceptor();
            cout << "\n\n\nSystem Message: Sign up successful!" << endl;
            cout << "\n\n\nSystem Message: Your user-ID is: " << newUser.getuserId() << endl;
            ch = _getch();
        }
    }
    static Acceptor findUserByEmailORId(string emailORId)
    {
        ifstream fin("users.txt");
        ifstream ft("account_data.txt");
        string line, line1;
        while (getline(fin, line) && getline(ft, line1))
        {
            string storedEmail, username, pass, Id, Bname, AccType, Tid;
            string accNum;
            string pincode;
            string balance;
            stringstream ss(line);
            stringstream ss1(line1);
            getline(ss, storedEmail, ',');
            getline(ss, username, ',');
            getline(ss, pass, ',');
            getline(ss, Id, ',');
            getline(ss1, accNum, ',');
            getline(ss1, Bname, ',');
            getline(ss1, AccType, ',');
            getline(ss1, Tid, ',');
            getline(ss1, pincode, ',');
            getline(ss1, balance, ',');
            if (storedEmail == emailORId || Id == emailORId)
            {
                Bank bank(Bname, stoll(accNum), AccType, Tid, pincode, stod(balance), 1);
                ft.close();
                fin.close();
                return Acceptor(username, storedEmail, pass, bank, Id, 1);
            }
        }
        ft.close();
        fin.close();
        return Acceptor();
    }
    void setMessage(string emailORId)
    {
        string storedEmail;
        string storedID;
        cout << endl;
        cout << "\n\t\t\tEnter the reason for fundraising including the amount you need: " << endl;
        cin >> ws;
        getline(cin, message);

        ifstream fin("Acceptor.txt");
        ofstream fout("temp.txt");
        string line;
        if (fout.is_open())
        {
            while (getline(fin, line))
            {
                stringstream ss(line);
                getline(ss, storedEmail, ',');
                getline(ss, storedID, ',');
                if (storedEmail == emailORId || storedID == emailORId)
                {
                    fout << email << "," << userId << "," << bankAccount.GetAccountNumber() << "," << message << "," << endl;
                }
                else
                {
                    fout << line << endl;
                }
            }
            fin.close();
            fout.close();
            remove("Acceptor.txt");
            rename("temp.txt", "Acceptor.txt");
        }
        else
        {
            cout << "\n\n\nSystem Error: Could not open file for writing!\n\n\n"
                 << endl;
            fin.close();
            fout.close();
        }
    }
    void login()
    {
        char ch;
        string email, password, username, currentPassword, newPassword, emailORId;
        string choice;
        int choice1 = 0;
        cout << "\n\t\t\tEnter your email or UserID: ";
        cin >> emailORId;
        cout << "\n\t\t\tEnter your password: ";
        cin >> password;
        Acceptor user = Acceptor::findUserByEmailORId(emailORId);
        if (user.getEmail() == "NaN")
        {
            cout << "\n\n\nSystem Error: User not found! Please try again with a valid email.\n\n\n"
                 << endl;
        }
        else
        {
            if (user.getPassword() == user.encryptPassword(password))
            {
                cout << "\n\n\nSystem Message: Login successful!\n\n\n"
                     << endl;
                do
                {
                    header();
                    cout << "\n\n\t----------------------------- ACCEPTOR ACCOUNT ------------------------------"; // acceptor
                    cout << "\n\n\t\t\t\t\t1. Check your Account Balance";
                    cout << "\n\t\t\t\t\t2. Change your Password";
                    cout << "\n\t\t\t\t\t3. Submit your reason for Fundraising\n";
                    cout << "\n\t\t\t\t\t4. LogOut\n";
                    cout << "\n\t-----------------------------------------------------------------------------\n\n";
                    cout << "\n\t\t\tEnter your choice (1-4): ";
                    choice = onlyTakeInteger("\t\t\tEnter your choice (1-4): ");
                    choice1 = stoi(choice);
                    switch (choice1)
                    {
                    case 1:
                        cout << endl;
                        cout << "\n\t\t\tYour current bank balance is: Rs. " << user.currentBalance() << endl;
                        ch = _getch();
                        break;
                    case 2:
                        cout << "\n\t\t\tEnter your current password: ";
                        cin >> currentPassword;
                        user.setPassword(currentPassword);
                        break;
                    case 3:
                        user.setMessage(emailORId);
                        ch = _getch();
                        break;
                    case 4:
                        cout << "\n\t\t\tLogout successful!" << endl;
                        break;
                    default:
                        cout << "\n\n\nInvalid choice! Please try again...\n\n\nPress any key to continue..." << endl;
                        ch = _getch();
                        break;
                    }
                } while (choice1 != 4);
            }
            else
            {
                cout << "\n\n\nMessage Error: Incorrect password! Please try again.\n\n\n"
                     << endl;
                ch = _getch();
            }
        }
    }
    friend class BankManager;
};
class Donor : public User
{
    int donorId;

public:
    Donor() : User() { donorId = 0; }
    Donor(string name, string email, string password, Bank &account, string Id = "D" + generateID()) : User(name, email, password, account, Id)
    {
        this->donorId = 0;
    }
    Donor(string username, string email, string pass, Bank &account, string Id, int n) : User(username, email, pass, account, Id, n)
    {
        donorId = 0;
    }
    void signup()
    {
        char ch;
        string email, password, username;
        cout << "\n\t\t\tEnter your email: ";
        do
        {
            int c = 0;
            cin >> email;
            if (validateEmail(email))
            {
                cout << "\n\t\t\tInvalid Email format!\n\n\t\t\tPlease enter email with valid format: " << endl;
                c = -1;
                ch = _getch();
            }
        } while (validateEmail(email));
        if (isEmailExist(email))
        {
            cout << "\n\n\nSystem Error: Email already exists! Please try again with a different email.\n\n\n"
                 << endl;
            ch = _getch();
        }
        else
        {
            char BankName[20];
            char accType[20];
            long long aNum;
            int pinCode;
            double balance;
            cout << "\n\t\t\tEnter your username: ";
            cin >> username;
            cout << "\n\t\t\tEnter your password: ";
            cin >> password;
            cout << "\n\t\t\tEnter your bank name:  ";
            cin >> ws;
            cin.getline(BankName, 19);
            cout << "\n\t\t\tEnter your Account Number: ";
            cin >> aNum;
            cout << "\n\t\t\tEnter account type:";
            cin >> ws;
            cin >> accType;
            cout << "\n\t\t\tEnter your PinCode: ";
            cin >> pinCode;
            cout << "\n\t\t\tEnter Account Balance: ";
            cin >> balance;
            Bank tempBank(string(BankName), aNum, string(accType), "1234456", to_string(pinCode), balance);
            Bank &t = tempBank;
            Donor newUser(username, email, password, tempBank, "D" + generateID());
            string a;
            a = newUser.getuserId();
            newUser.setBalance(balance);
            newUser.saveToFile();

            cout << "\n\n\nSystem Message: Sign up successful!" << endl;
            cout << "\n\n\nSystem Message: Your user-ID is: " << newUser.getuserId() << endl;
            ch = _getch();
        }
    }
    static Donor findUserByEmailORId(string emailORId)
    {
        ifstream fin("users.txt");
        ifstream ft("account_data.txt");
        string line, line1;
        while (getline(fin, line) && getline(ft, line1))
        {
            string storedEmail, username, pass, Id, Bname, AccType, Tid;
            string accNum;
            string pincode;
            string balance;
            stringstream ss(line);
            stringstream ss1(line1);
            getline(ss, storedEmail, ',');
            getline(ss, username, ',');
            getline(ss, pass, ',');
            getline(ss, Id, ',');
            getline(ss1, accNum, ',');
            getline(ss1, Bname, ',');
            getline(ss1, AccType, ',');
            getline(ss1, Tid, ',');
            getline(ss1, pincode, ',');
            getline(ss1, balance, ',');
            if (storedEmail == emailORId || Id == emailORId)
            {
                Bank bank(Bname, stoll(accNum), AccType, Tid, pincode, stod(balance), 1);
                ft.close();
                fin.close();
                return Donor(username, storedEmail, pass, bank, Id, 1);
            }
        }
        ft.close();
        fin.close();
        return Donor();
    }
    void Donate(Donor &x, long long y, double amount) const;
    void login()
    {
        char ch;
        string email, password, username, currentPassword, newPassword, emailORId, msg;
        string choice;
        string Id;
        string accountNum;
        string line;
        int choice1 = 0;
        cout << "\n\t\t\tEnter your email or UserID: ";
        cin >> emailORId;
        cout << "\n\t\t\tEnter your password: ";
        cin >> password;
        Donor dnr = Donor::findUserByEmailORId(emailORId);
        if (dnr.getEmail() == "NaN")
        {
            cout << "\n\n\nSystem Error: User not found! Please try again with a valid email.\n\n\n"
                 << endl;
            ch = _getch();
        }
        else
        {
            if (dnr.getPassword() == dnr.encryptPassword(password))
            {
                cout << "\n\t\t\tSystem Message: Login successful!\n\n\n"
                     << endl;
                do
                {
                    header();
                    cout << "\n\n\t------------------------------- DONOR ACCOUNT -------------------------------"; // account
                    cout << "\n\n\t\t\t\t\t1. Donate now!";
                    cout << "\n\t\t\t\t\t2. Check your Account Balance";
                    cout << "\n\t\t\t\t\t3. Change your Password\n";
                    cout << "\n\t\t\t\t\t4. LogOut\n";
                    cout << "\n\t-----------------------------------------------------------------------------\n\n";
                    cout << "\n\t\t\tEnter your choice (1-4): ";
                    choice = onlyTakeInteger("\t\t\tEnter your choice (1-4): ");
                    choice1 = stoi(choice);
                    switch (choice1)
                    {
                    case 1:
                        double amount;
                        long long accptracc;
                        {
                            ifstream fin;
                            fin.open("Acceptor.txt");
                            if (!fin)
                            {
                                cout << "\n\n\nSystem Error: Error opening file!\n\n\n";
                            }
                            else
                            {
                                cout << "\n\n\n\t-----------------------------------------------------------------------------------------------------------------------------";
                                cout << "\n\t|Acceptor ID| " << "\t" << "|\t\tAcceptor email\t |" << "\t" << "|Acceptor Account Number|" << endl;
                                cout << "\n\t-----------------------------------------------------------------------------------------------------------------------------\n\n\n";
                                while (getline(fin, line))
                                {
                                    stringstream ss(line);
                                    getline(ss, email, ',');
                                    getline(ss, Id, ',');
                                    getline(ss, accountNum, ',');
                                    getline(ss, msg, ',');
                                    cout << "\t|" << Id << " " << " " << " " << "|" << "\t|" << email << "\t\t |" << "\t|\t" << accountNum << "\t\t|" << endl;
                                    cout << "\tMessage: << " << msg << " >>\n";
                                }
                                cout << "\n\n\t----------------------------------------------------------------------------------------------------------------------------";
                                cout << "\n\t----------------------------------------------------------------------------------------------------------------------------\n\n\n";
                                ch = _getch();
                            }
                            fin.close();
                        }
                        cout << endl;
                        cout << "\n\t\t\tEnter Account number to donate to: " << endl;
                        cin >> accptracc;
                        cout << "\n\t\t\tEnter the amount of donation: " << endl;
                        cin >> amount;
                        dnr.Donate(dnr, accptracc, amount);
                        break;
                    case 2:
                        cout << endl;
                        cout << "\n\t\t\tYour current bank balance is: Rs. " << dnr.currentBalance() << endl;
                        ch = _getch();
                        break;
                    case 3:
                        cout << "\n\t\t\tEnter your current password: ";
                        cin >> currentPassword;
                        dnr.setPassword(currentPassword);
                        break;
                    case 4:
                        cout << "\n\n\nSystem Message: Logout successful!\n\n\n";
                        break;
                    default:
                        cout << "\n\n\nInvalid choice! Please try again...\n\nPress any key to continue..." << endl;
                        ch = _getch();
                        break;
                    }
                } while (choice1 != 4);
            }
            else
            {
                cout << "\n\n\nSystem Error: Incorrect password! Please try again.\n\n\n"
                     << endl;
                ch = _getch();
            }
        }
    }
    friend class BankManager;
};
class BankManager
{
public:
    static void TransferMoney(Donor &x, long long y, double amount);
    static void UpdateAccountInfo(const Bank &account);
    static bool AccountExists(long long accountNumber);
};
void BankManager::TransferMoney(Donor &x, long long y, double amount)
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
                }
                else
                {
                    tempFile << accountNumber << "," << bankName << "," << accountType << "," << transactionId << "," << pinCode << "," << bal << "," << endl;
                    tempFile << "***********" << endl;
                }
            }
            inputFile.close();
            tempFile.close();
            remove("account_data.txt");
            rename("temp_data.txt", "account_data.txt");
        }
        else
        {
            cout << "\n\n\nSystem Error: Unable to open file for account information update.\n\n\n"
                 << endl;
            ch = _getch();
        }
    }
    else
    {
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
void Donor::Donate(Donor &x, long long y, double amount) const
{
    BankManager::TransferMoney(x, y, amount);
}
class FundManager : public User
{
    int managerId;

public:
    FundManager() : User()
    {
        managerId = 0;
    }
    FundManager(string name, string email, string password, Bank &account, int managerId) : User(name, email, password, account)
    {
        this->managerId = managerId;
    }
    int getManagerId()
    {
        return managerId;
    }
};
void header()
{
    system("CLS");
    cout << "\t\t\t\tC++ OOP DONATE NOW PROJECT:" << endl;
    cout << "\t\t\t\tMembers: " << endl;
    cout << "\t\t\t\tk224599 Umer Ahmed BCS-2C" << endl;
    cout << "\t\t\t\tk224494 Fasih BCS-2C" << endl;
    cout << "\t\t\t\tk224648 Jawwad Ahmed BCS-2C" << endl;
    return;
}
void load()
{
    char a = 177, b = 219;
    cout << "\n\n\n\t\t\t\t ";
    for (int i = 0; i < 25; i++)
        cout << a;
    cout << "]\r\t\t\tLoading [";
    for (int i = 0; i < 25; i++)
    {
        sleep(1);
        cout << b;
    }
    cout << "]\n\n\n";
    sleep(2);
}
int main()
{
    Donor donor;
    Acceptor acceptor;
    string email, password, username, currentPassword, newPassword, emailORId;
    string choice;
    int choice1 = 0, choice2 = 0;
    char ch;
    do
    {
        header();
        cout << "\n\n\t--------------------------------- Main Menu ---------------------------------";
        cout << "\n\n\t\t\t\t\t1. Enter as Donor";
        cout << "\n\t\t\t\t\t2. Enter as Acceptor";
        cout << "\n\t\t\t\t\t3. Quit Program\n";
        cout << "\n\t-----------------------------------------------------------------------------\n\n";
        cout << "\n\t\t\tEnter your choice (1-3): ";
        choice = onlyTakeInteger("\t\t\tEnter your choice (1-3): ");
        choice1 = stoi(choice);
        switch (choice1)
        {
        case 1:
        {
            do
            {
                header();
                cout << "\n\n\t-------------------------------- DONOR MENU ---------------------------------";
                cout << "\n\n\t\t\t\t\t1. SignUp for a Donor Account";
                cout << "\n\t\t\t\t\t2. LogIn into a Donor Account";
                cout << "\n\t\t\t\t\t3. Back to Main Menu\n";
                cout << "\n\t-----------------------------------------------------------------------------\n\n";
                cout << "\n\t\t\tEnter your choice (1-3): ";
                choice = onlyTakeInteger("\t\t\tEnter your choice (1-3): ");
                choice2 = stoi(choice);
                switch (choice2)
                {
                case 1:
                    donor.signup();
                    break;
                case 2:
                    donor.login();
                    break;
                case 3:
                    load();
                    break;
                default:
                    cout << "\n\n\nInvalid choice! Please try again...\n\nPress any key to continue..." << endl;
                    ch = _getch();
                    break;
                }
            } while (choice2 != 3);
        }
        break;
        case 2:
        {
            do
            {
                header();
                cout << "\n\n\t------------------------------ ACCEPTOR MENU --------------------------------";
                cout << "\n\n\t\t\t\t\t1. SignUp for an Acceptor Account";
                cout << "\n\t\t\t\t\t2. LogIn into an Acceptor Account";
                cout << "\n\t\t\t\t\t3. Back to Main Menu\n";
                cout << "\n\t-----------------------------------------------------------------------------\n\n";
                cout << "\n\t\t\tEnter your choice (1-3): ";
                choice = onlyTakeInteger("\t\t\tEnter your choice (1-3): ");
                choice2 = stoi(choice);
                switch (choice2)
                {
                case 1:
                    acceptor.signup();
                    break;
                case 2:
                    acceptor.login();
                    break;
                case 3:
                    load();
                    break;
                default:
                    cout << "\n\n\nInvalid choice! Please try again...\n\nPress any key to continue..." << endl;
                    ch = _getch();
                    break;
                }
            } while (choice2 != 3);
        }
        break;
        case 3:
            cout << "\n\n\t-------------------------------- GOODBYE!! ----------------------------------\n\n\n\n\n\n\n\n\n\n\n\n\n";
            break;
        default:
            cout << "\n\n\nInvalid choice! Please try again...\n\nPress any key to continue..." << endl;
            ch = _getch();
            break;
        }
    } while (choice1 != 3);
    return 0;
}
