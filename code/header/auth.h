#pragma once

#include "./utils.h"
#include "./menu.h"
#include "./person.h"
#include "./doctor.h"
#include "./patient.h"
#include "./files.h"
/*
email validation '@'
password validation
phone no. validation
optional 👇
age validation
height validation
*/

class Auth : public FileManage
{
public:
    // role = doc | pat; action = login | signup
    static Person *auth(string role, string action, string banner)
    {
        string name, email, phone, password, passwordConfirm, specialization, qualification, bloodGrp, input, dataContents;
        char gender, ans;
        float height, weight;
        int age, ID, itr = 0;
        Person *person = nullptr;

        IDs both = getIDs();

    wrong_info:
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
                cout << "Qualification: ";
                getline(cin, qualification);
            }
            else
            {
                bloodGrp = Menu::mini(grpNames, "Blood Group: ");
                gender = Menu::mini(genderClass, "Gender: ");
                height = Menu::number(1, 300, "Height: ", "cm");
                weight = Menu::number(1, 250, "Weight: ", "kgs");
                age = Menu::number(0, 120, "Age: ", "yrs");
            }

            vector<char> confirm = {'Y', 'n'};
            ans = Menu::mini(confirm, "Is the above info correct [Y/n]: ");
            if (ans == 'n')
                goto wrong_info;

            if (role == "doc")
            {
                ID = ++both.docID;
                person = new Doctor(name, email, phone, password, specialization, qualification, ID);
                createDoc((Doctor *)person);
            }
            else
            {
                ID = ++both.MR;
                person = new Patient(name, email, phone, password, age, gender, bloodGrp, height, weight, ID);
                createPat((Patient *)person);
            }
            updateIDs(both);
            return person;
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