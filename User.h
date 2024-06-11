#ifndef USER_H
#define USER_H

#include "Bank.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;

string onlyTakeInteger(string x);

class User
{
protected:
    string userId;
    string username;
    string email;
    string password;
    Bank bankAccount;

    static string generateID();

public:
    User();
    User(string Username, string Email, string pass, Bank &account, string Id);
    User(string username, string email, string pass, Bank &account, string Id, int n);
    double currentBalance();
    void setBalance(double bal);
    bool validateEmail(string email);
    bool isPasswordValid(string password);
    string encryptPassword(string x);
    string getUsername() const;
    string getEmail() const;
    string getPassword() const;
    string getuserId();
    void setPassword(string currentPassword);
    void setUsername();
    void saveToFile() const;
    void saveForAcceptor() const;
    void updateFile() const;
    static User findUserByEmailORId(string emailORId);
    static bool isEmailExist(string email);
    static bool isIDExist(string Id);
    void virtual signup();
    void virtual login();
    
    friend class BankManager;
};

#endif