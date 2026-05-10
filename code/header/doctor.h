#pragma once

#include "./person.h"

class Doctor : public Person
{
protected:
    string specialization, qualification;
    int ID;

public:
    Doctor(string name, string email, string phone, string password, string specialization, string qualification, int ID) : Person(name, email, phone, password), specialization(specialization), qualification(qualification), ID(ID) {}

    void dashboard(string banner) override
    {
        vector<string> opt = {"Check Patient",
                              "Check Appointments",
                              "Change Availibility",
                              "View Profile",
                              "Change Profile",
                              "View Patient's Medical History"};
        vector<int> flags(opt.size(), 0);
        string heading = banner + "\e[1;32mWelcome Doc. " + name + "\e[0m\n\n";
        Menu::full(opt, flags, heading);
    }

    void displayProfile() override
    {
        cout << "Specialization: " << specialization << endl;
    }

    string getSpec() { return specialization; }
    string getQuali() { return qualification; }
    int getID() { return ID; }
};