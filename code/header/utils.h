#pragma once

#include <string>
#include <vector>

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
protected:
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

#ifdef _WIN32
    static void initConsole()
    {
        SetConsoleOutputCP(CP_UTF8);

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(hOut, &mode);
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, mode);
    }
#endif

    static void clear()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static void clearLine()
    {
        cout << "\e[2K\e[G";
    }

    static string getKeys()
    {
        char ch = getch();
        if (ch == 0 || ch == -32 || ch == '\e')
        {
#ifdef __linux__
            getch();
#endif
            ch = getch();
            switch (ch)
            {
            case 'A':
            case 'H':
                return "UP";
            case 'B':
            case 'P':
                return "DN";
            case 'C':
            case 'M':
                return "RT";
            case 'D':
            case 'K':
                return "LT";
            }
        }

        if (ch == '\n' || ch == '\r')
            return "ENT";
        if (ch == '\t')
            return "TAB";
        if (ch == 127 || ch == '\b')
            return "BCK";

        return std::string(1, ch);
    }

    static string getPassword()
    {
        setEcho(false);
        string password;
        cin.ignore();
        getline(cin, password);
        setEcho(true);
        return password;
    }
};