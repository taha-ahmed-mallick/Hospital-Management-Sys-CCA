#pragma once

#include "./person.h"

class Doctor : public Person
{
protected:
    string specialization, qualification;
    int ID;
    void setSpec(string val) {specialization = val;}
    void setQuali(string val) {qualification = val;}

public:
    Doctor(string name, string email, string phone, string password, string specialization, string qualification, int ID) : Person(name, email, phone, password), specialization(specialization), qualification(qualification), ID(ID) {}
    void dashboard(string banner) override
    {
        vector<string> opt = {"Check Patient",
                              "View Schedule",
                              "Change Availibility",
                              "View Profile",
                              "Change Profile",
                              "Logout"};
        vector<int> flags(opt.size(), 0);
        flags[opt.size() - 1] = 1;
        string heading = banner + "\e[1;32mWelcome Doc. " + name + "\e[0m\n\n";
        while (true)
        {
            int select = Menu::full(opt, flags, heading);
            switch (select)
            {
            case 0:
                /* code */
                break;
            case 1:
                /* code */
                break;
            case 2:
                /* code */
                break;
            case 3:
                Utils::clear();
                displayProfile();
                cout << "\nPress any key to return...";
                Utils::getch();
                break;
            case 4:
                break;
            case 5:
                return;
                break;
            default:
                break;
            }
        }
    }

    void displayProfile() override
    {
        cout << "\n--- Doctor Profile ---\n";
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Specialization: " << specialization << endl;
        cout << "Qualification: " << qualification << endl;
        cout << "Doctor ID: " << ID << endl;
    }

    string getSpec() { return specialization; }
    string getQuali() { return qualification; }
    int getID() { return ID; }
};