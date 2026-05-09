#pragma once

#include "./utils.h"
#include "./menu.h"
/*
email validation '@'
password validation
phone no. validation
optional 👇
age validation
height validation
*/

class Auth
{
public:
    // role = doc | pat; action = login | signup
    static void auth(string role, string action, string banner)
    {
        Utils::clear();
        cout << banner << "\e[1;33m";
        if (action == "login")
            cout << "Logging in";
        else
            cout << "Signing up";
        cout << " as a ";
        if (role == "doc")
            cout << "Doctor!";
        else
            cout << "Patient!";
        cout << "\n\n\e[0m";

        string name, email, phone, password, passwordConfirm, specialization, bloodGrp, input;
        char gender;
        float height, weight;
        int age, ID, itr = 0;

        vector<string> grpNames = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
        vector<char> genderClass = {'M', 'F'};

        if (action == "signup")
        {
            cout << "Name: ";
            getline(cin, name);
            cout << "Email: ";
            getline(cin, email);
            cout << "Phone Number \e[34m(03XXXXXXXXX)\e[0m: ";
            getline(cin, phone);

            do
            {
                if (itr > 1)
                    cout << "\e[A";
                if (itr)
                    cout << "\r\e[A\e[J\e[1;31mPasswords don't match!!!\e[0m\n";
                cout << "Password: ";
                password = Utils::getPassword();
                cout << "\nConfirm Password: ";
                passwordConfirm = Utils::getPassword();
                if (password == passwordConfirm)
                {
                    if (itr)
                        cout << "\e[A";
                    cout << "\r\e[A\e[J\e[1;32mPasswords matched.\e[0m\n";
                }
                itr++;
            } while (password != passwordConfirm);

            if (role == "doc")
            {
                cout << "Specialization: ";
                getline(cin, specialization);
            }
            else
            {
                bloodGrp = Menu::mini(grpNames, "Blood Group: ");
                gender = Menu::mini(genderClass, "Gender: ");
                height = Menu::number(0, 300, "Height: ", "cm");
                weight = Menu::number(0, 250, "Weight: ", "kgs");
                age = Menu::number(0, 120, "Age: ", "yrs");
            }
        }
        else
        {
            if (role == "doc")
                cout << "Enter your ID: ";
            else
                cout << "Enter your MR#: ";
            getline(cin, input);
            ID = stoi(input);
            cout << "Enter Password: ";
            password = Utils::getPassword();
            cout << password << endl;
        }
    }
};