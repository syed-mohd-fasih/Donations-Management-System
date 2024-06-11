#include "User.h"

using namespace std;

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

string User ::generateID()
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

User ::User() : username("NaN"), email("NaN"), password("NaN"), userId("NaN"), bankAccount(*(new Bank())) {}
User ::User(string Username, string Email, string pass, Bank &account, string Id = generateID()) : bankAccount(account)
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
                m = Id.substr(0, 4) + "0" + m;
            Id = m;
        }
    }
    this->userId = Id;
    saveToFile();
}
User ::User(string username, string email, string pass, Bank &account, string Id, int n) : bankAccount(account)
{
    this->username = username;
    this->email = email;
    this->password = pass;
    this->userId = Id;
}
double User ::currentBalance()
{
    return bankAccount.GetBalance();
}
void User ::setBalance(double bal)
{
    bankAccount.SetBalance(bal);
}
bool User ::validateEmail(string email)
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
bool User ::isPasswordValid(string password)
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
        cout << "\nYour password must contain at least one special character.\n";
    if (!hasUpperCase)
        cout << "\nYour password must contain at least one uppercase letter.\n";
    if (!hasLowerCase)
        cout << "\nYour password must contain at least one lowercase letter.\n";
    if (!hasNumber)
        cout << "\nYour password must contain at least one numeric character.\n";
    if (password.size() < 6)
        cout << "\nYour password must be at least 6 characters long.\n";

    return hasSpecialChar && hasUpperCase && hasLowerCase && hasNumber && password.size() >= 6;
}
string User ::encryptPassword(string x)
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
            x[i] += 2;
        else
            x[i] -= 2;
    }
    x = x + Mark;
    return x;
}
string User ::getUsername() const
{
    return username;
}
string User ::getEmail() const
{
    return email;
}
string User ::getPassword() const
{
    return password;
}
string User ::getuserId()
{
    return userId;
}
void User ::setPassword(string currentPassword)
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
void User ::setUsername()
{
    string name;
    cout << "\n\t\t\tEnter your new Username: ";
    cin >> username;
    updateFile();
    cout << "\n\n\nSystem Messge: Username updated successfully!\n\n\n"
         << endl;
}
void User ::saveToFile() const
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
void User ::saveForAcceptor() const
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
void User ::updateFile() const
{
    ifstream fin("users.txt");
    ofstream fout("temp.txt");
    string line;
    while (getline(fin, line))
    {
        string storedEmail = line.substr(0, line.find(","));
        if (storedEmail == email)
            fout << email << "," << username << "," << password << "," << userId << "," << endl;
        else
            fout << line << endl;
    }
    fin.close();
    fout.close();
    remove("users.txt");
    if (!rename("temp.txt", "users.txt"))
        cout << "\n\n\nSystem Message: File Update Success\n\n\n";
    else
        cout << "\n\n\nSystem Message: File Update Failed\n\n\n";
}
User User ::findUserByEmailORId(string emailORId)
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
bool User ::isEmailExist(string email)
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
bool User ::isIDExist(string Id)
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
void User ::signup()
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
void User ::login()
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