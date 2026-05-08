#pragma once

#include "./utils.h"

class Menu
{
public:
    static int full(vector<string> opt, vector<int> flags, string before = "")
    {
        int selected = 0, size = opt.size();
        string key;
        do
        {
            Utils::clear();
            cout << before;
            cout << "Use arrow keys to navigate:\n\n";
            for (int i = 0; i < size; i++)
            {
                cout << "\033[1m";
                if (flags[i] == 1)
                    cout << "\033[31m";
                if (i == selected)
                {
                    if (flags[i] == 0)
                        cout << "\033[32m";
                    cout << "\033[4m> ";
                }
                cout << opt[i] << endl;
                cout << "\033[0m";
            }
            cout << "\nPress ENTER to select.";
            string key = Utils::getKeys();
            if (key == "UP")
                selected--;
            else if (key == "DN")
                selected++;
            else if (key == "ENT")
                return selected;
            if (selected < 0)
                selected = 0;
            if (selected >= size)
                selected = size - 1;
        } while (true);
    }

    static int mini(vector<string> opt, string text = "")
    {
        int selected = 0, size = opt.size();
        string key;
        do
        {
            Utils::clearLine();
            cout << text << "\e[1;36m" << opt[selected] << " \e[33m(Use Arrow keys)\e[0m";
            cout.flush();
            key = Utils::getKeys();
            if (key == "UP" || key == "LT")
            selected--;
            else if(key == "DN" || key == "RT")
            selected++;
            else if(key == "ENT")
            return selected;
            if (selected < 0)
                selected = size -1;
            else if (selected >= size)
                selected = 0;
        } while (true);
    }
};