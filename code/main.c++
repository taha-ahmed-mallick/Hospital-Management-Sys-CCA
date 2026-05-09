#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "./header/utils.h"
#include "./header/menu.h"
#include "./header/doctor.h"
#include "./header/patient.h"
#include "./header/auth.h"
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
        Auth::auth("doc", "login", heading);
        break;
    case 1:
        Auth::auth("doc", "signup", heading);
        break;
    case 2:
        Auth::auth("pat", "login", heading);
        break;
    case 3:
        Auth::auth("pat", "signup", heading);
        break;
    case 4:
        cout << "\nExiting...\n";
        return 0;
        break;
    default:
        break;
    }

    return 0;
}

// Menu::mini(bloodGrp, "Blood Group: ");
// Patient patient("Taha", "taha@gmail.com", "0333-2946715", "letmein", 18, 'M', "B+", 185, 68, 1995514);
// patient.displayProfile();
// return 1;