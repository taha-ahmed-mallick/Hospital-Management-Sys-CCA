#pragma once

#include <string>

#ifdef _WIN32
#include <direct.h>
#include <cerrno>
#include <windows.h>
#include <conio.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#else
#include <filesystem>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#endif

using namespace std;

class Utils
{
private:
public:
    static int createDir(const string &path)
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

    static char getch()
    {
#ifdef _WIN32
        return _getch();
#else
        termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        char ch = std::cin.get();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
#endif
    }

    static void setEcho(bool enable)
    {
#ifdef _WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

        DWORD mode;
        GetConsoleMode(hStdin, &mode);

        if (enable)
            mode |= ENABLE_ECHO_INPUT;
        else
            mode &= ~ENABLE_ECHO_INPUT;

        SetConsoleMode(hStdin, mode);
#else
        termios tty;
        tcgetattr(STDIN_FILENO, &tty);
        if (enable)
            tty.c_lflag |= ECHO;
        else
            tty.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
    }

#ifdef _WIN32
    satic void initConsole()
    {
        SetConsoleOutputCP(CP_UTF8);

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        DWORD mode = 0;
        GetConsoleMode(hOut, &mode);

        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        SetConsoleMode(hOut, mode);
    }
#endif

    static void clear() {
        cout << "\033[2J\033[H";
    }
};