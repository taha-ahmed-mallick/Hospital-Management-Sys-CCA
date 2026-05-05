#pragma once

#include <string>

#ifdef _WIN32
#include <direct.h>
#include <cerrno>
#else
#include <filesystem>
#endif

using namespace std;

int createDir(const string &path);