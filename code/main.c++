#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "./header/utils.h"
using namespace std;

int main()
{
#ifdef _WIN32
    Utils::initConsole();
#endif
    string folders[] = {"doctors/", "patients/"};
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
    cout << "\033[1;34m\t┌──────────────────────────┐\n"
                    <<"\t│Hospital Management System│\n"
                    <<"\t└──────────────────────────┘\033[0m\n";
    return 0;
}