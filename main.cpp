#include <iostream>
#include <string>
#include <Windows.h>

#include "User.h"
#include "Bank.h"
#include "BankManager.h"

using namespace std;


void header()
{
    system("CLS");
    cout << "\t\t\t\tC++ OOP DONATE NOW PROJECT:" << endl
         << "\t\t\t\tMembers: " << endl
         << "\t\t\t\tk224599 Umer Ahmed BCS-2C" << endl
         << "\t\t\t\tk224494 Fasih BCS-2C" << endl
         << "\t\t\t\tk224648 Jawwad Ahmed BCS-2C" << endl;
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
        Sleep(10);
        cout << b;
    }
    cout << "]\n\n\n";
    Sleep(20);
}

int main()
{
    User donor, acceptor;
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