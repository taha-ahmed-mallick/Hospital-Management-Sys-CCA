#include "./header/dirmanage.h"

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
        return 0;
    }
#endif
}