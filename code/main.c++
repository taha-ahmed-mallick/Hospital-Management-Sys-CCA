#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <direct.h>
#include <cerrno>
#else
#include <filesystem>
#endif
using namespace std;

int createDir(const string &path)
{
#ifdef _WIN32
    errno = 0;
    if (_mkdir(path.c_str()) == 0)
        return 1;
    else if (errno == EEXIST)
        return -1;
    else
        return 0;
#else
    try
    {
        if (filesystem::create_directory(path))
            return 1;
        else
            return -1;
    }
    catch (const filesystem::filesystem_error &e)
    {
        cout << e.what() << endl;
        return 0;
    }
#endif
}

int main()
{
    string folders[] = {"doctors/", "patients/"};
    int folderLen = sizeof(folders)/sizeof(folders[0]);
    for (int i = 0; i < folderLen; i++)
    {
        if (!createDir("./"+folders[i]))
            cout << "Required folders can't be generated!!\n";
    }
    return 0;
}