#include <iostream>
#include <vector>
#include "./header/utils.h"
#include "./header/menu.h"
#include "./header/person.h"
#include "./header/doctor.h"
#include "./header/patient.h"
#include "./header/auth.h"
#include "./header/files.h"
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

    vector<string> day = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    int today = FileManage::initializeData();

    string heading = "\e[1;34m\t┌──────────────────────────┐\n\t│Hospital Management System│\e[0m\e[1;36m\t" + day.at(today) + "\e[0m\e[1;34m\n\t└──────────────────────────┘\e[0m" + "\n\n\n";
    vector<string> opt = {"Login as a Doctor",
                          "Signup as a Doctor",
                          "Login as a Patient",
                          "Signup as a Patient",
                          "EXIT"};
    vector<int> flags = {0, 0, 0, 0, 1}; // for coloring purposes
    while (true)
    {
        int select = Menu::full(opt, flags, heading);
        switch (select)
        {
        case 0:
        {
            try
            {
                Doctor *doc = (Doctor *)Auth::auth("doc", "login", heading);
                doc->dashboard(heading);
                delete doc;
                doc = nullptr;
            }
            catch (string err)
            {
            }
            break;
        }
        case 1:
        {
            Doctor *doc = (Doctor *)Auth::auth("doc", "signup", heading);
            doc->dashboard(heading);
            delete doc;
            doc = nullptr;
            break;
        }
        case 2:
        {
            try
            {
                Patient *pat = (Patient *)Auth::auth("pat", "login", heading);
                pat->dashboard(heading);
                delete pat;
                pat = nullptr;
            }
            catch (string err)
            {
            }
            break;
        }
        case 3:
        {
            Patient *pat = (Patient *)Auth::auth("pat", "signup", heading);
            pat->dashboard(heading);
            delete pat;
            pat = nullptr;
            break;
        }
        case 4:
            cout << "\nExiting...\n";
            FileManage::updateDay();
            return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}