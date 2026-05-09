#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "./header/utils.h"
#include "./header/menu.h"
using namespace std;

int main()
{
#ifdef _WIN32
    Utils::initConsole();
#endif
    string folders[] = {"records/", "records/doctors/", "records/patients/"};
    int folderLen = sizeof(folders) / sizeof(folders[0]);
    for (int i = 0; i < folderLen; i++)
    {
        if (!Utils::createDir("./" + folders[i]))
        {
            cout << "Required folders can't be generated!!\n"
                 << "Exiting...";
            return 1;
        }
    }

    string heading = "\e[1;34m\t┌──────────────────────────┐\n\t│Hospital Management System│\n\t└──────────────────────────┘\e[0m\n\n\n";
    vector<string> opt = {"Login as a Doctor",
                          "Signup as a Doc",
                          "Login as a Patient",
                          "Signup as a Patient",
                          "EXIT"};
    vector<int> flags = {0, 0, 0, 0, 1};
    int select = Menu::full(opt, flags, heading);

    vector<string> bloodGrp = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    vector<char> gender = {'M', 'F'};

    switch (select)
    {
    case 0:
    {
        Utils::clear();
        cout << heading
             << "\e[1;33mLoging in as a Doctor\n\n\e[0m";
        string email, password;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        password = Utils::getPassword();
        break;
    }
    case 1:
    {
        Utils::clear();
        cout << heading
             << "\e[1;33mSigning up as a Doctor\n\n\e[0m";
        string email, password;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        password = Utils::getPassword();
        break;
    }
    case 2:
    {
        Utils::clear();
        cout << heading
             << "\e[1;33mLoging in as a Patient\n\n\e[0m";
        string email, password;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        password = Utils::getPassword();
        break;
    }
    case 3:
    {
        Utils::clear();
        cout << heading
             << "\e[1;33mSigning up as a Patient\n\n\e[0m";
        string email, password, name;
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        password = Utils::getPassword();
        break;
    }
    case 4:
        cout << "\nExiting...\n";
        return 0;
        break;

    default:
        break;
    }

    return 0;
}