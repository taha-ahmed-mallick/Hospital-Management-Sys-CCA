#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "./header/dirmanage.h"
using namespace std;

int main()
{
    string folders[] = {"doctors/", "patients/"};
    int folderLen = sizeof(folders) / sizeof(folders[0]);
    for (int i = 0; i < folderLen; i++)
    {
        if (!createDir("./" + folders[i]))
        {
            cout << "Required folders can't be generated!!\n"
                 << "Exiting...";
            return 1;
        }
    }
    return 0;
}