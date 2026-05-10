#pragma once

#include "./utils.h"
#include "./menu.h"
#include "./person.h"
#include "./doctor.h"
#include "./patient.h"
#include "./files.h"
/*
password validation
optional 👇
age validation
height validation
*/
static bool isValidName(const string &name){
    if (name.empty()) 
        return false;

    for (char c : name)
    {
        if (!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}
static bool isValidPhone(const string &phone){
    if (phone.length() != 11)
        return false;

    for (char c : phone)
    {
        if (!isdigit(c))
            return false;
    }

    return true;
}
static bool isValidEmail(const string &email){
    if (email.empty())
        return false;

    if (email.find('@') == string::npos) // @ character not found
        return false;

    if (email.find('.') == string::npos) // character not found Checks if email contains a dot:
        return false;

    if (email[0] == '@' || email[0] == '.')
        return false;

    if (email[email.length() - 1] == '@' || email[email.length() - 1] == '.')
        return false;

    for (char c : email)
    {
        if (c == ' ')
            return false;
    }

    return true;
}
static bool isValidPassword(const string &password){
    if (password.length() < 8 || password.length() > 17)
        return false;

    if (password[0] == '|')
        return false;

    return true;
}
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
            do{
                cout << "Name: ";
                getline(cin, name);

                if (!isValidName(name))
                    cout << "\e[1;31mInvalid name! Only Alphabets allowed.\e[0m\n";

            }while(!isValidName(name));
            do{
                cout << "Email: ";
                getline(cin, email);

                if (!isValidEmail(email))
                    cout << "\e[1;31mInvalid email format!\e[0m\n";

            }while(!isValidEmail(email));
            do{
                cout << "Phone Number (03XXXXXXXXX): ";
                getline(cin, phone);

                 if (phone.length() != 11){
                    cout << "\e[1;31mPhone number must contain exactly 11 digits!\e[0m\n";
                }
                else if (!isValidPhone(phone)){
                    cout << "\e[1;31mPhone number must contain digits only!\e[0m\n";
                }

            }while(!isValidPhone(phone));
      while (true)
{
    cout << "Password: ";
    password = Utils::getPassword();

    // STEP 1: validation
    if (!isValidPassword(password))
    {
        cout << "\n\e[1;31mPassword must be 8-17 characters and cannot start with '|'\e[0m\n";
        continue;
    }

    cout << "\nConfirm Password: ";
    passwordConfirm = Utils::getPassword();

    // STEP 2: match check
    if (password != passwordConfirm)
    {
        cout << "\n\e[1;31mPasswords do not match! Try again.\e[0m\n";
        continue;
    }

    // success
    cout << "\n\e[1;32mPassword set successfully!\e[0m\n";
    break;
}
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