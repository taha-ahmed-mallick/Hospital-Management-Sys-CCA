#pragma once

#include "./utils.h"

class Menu : protected Utils
{
public:
    static int full(const vector<string>& opt, const vector<int>& flags, string before = "")
    {
        int selected = 0, size = opt.size();
        string key;
        do
        {
            clear();
            cout << before;
            cout << "Use arrow keys to navigate:\n\n";
            for (int i = 0; i < size; i++)
            {
                cout << "\e[1m";
                if (flags[i] == 1)
                    cout << "\e[31m";
                if (i == selected)
                {
                    if (flags[i] == 0)
                        cout << "\e[32m";
                    cout << "\e[4m> ";
                }
                cout << opt[i] << endl;
                cout << "\e[0m";
            }
            cout << "\nPress ENTER to select.";
            string key = getKeys();
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

    template <typename T>
    static T mini(const vector<T>& opt, string text = "")
    {
        int selected = 0, size = opt.size();
        string key;
        do
        {
            clearLine();
            cout << text << "\e[1;36m" << opt[selected] << " \e[33m(Use Arrow keys)\e[0m";
            cout.flush();
            key = getKeys();
            if (key == "UP" || key == "LT")
                selected--;
            else if (key == "DN" || key == "RT")
                selected++;
            else if (key == "ENT")
                return opt[selected];
            if (selected < 0)
                selected = size - 1;
            else if (selected >= size)
                selected = 0;
        } while (true);
    }
};