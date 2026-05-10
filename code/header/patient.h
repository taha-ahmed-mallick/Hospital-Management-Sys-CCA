#pragma once

#include "./person.h"

class Patient : public Person
{
protected:
    char gender;
    string bloodGrp;
    int height, age, MR_num;
    float weight;

public:
    Patient(string name, string email, string phone, string password, int age, char gender, string bloodGrp, int height, float weight, int MR_num) : Person(name, email, phone, password), gender(gender), bloodGrp(bloodGrp), height(height), weight(weight), MR_num(MR_num), age(age) {}

    void dashboard(string banner) override
    {
        vector<string> opt = {"Book Appointment",
                              "View Appointment",
                              "View Profile",
                              "Change Profile",
                              "View Your Medical History",
                              "Logout"};
        vector<int> flags(opt.size(), 0);
        flags[opt.size() - 1] = 1;
        string heading = banner + "\e[1;32mWelcome " + name + "\e[0m\n\n";
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
                /* code */
                break;
            case 4:
                /* code */
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
        cout << "Gender: " << gender << endl;
    }

    char getGender() { return gender; }
    string getBloodGrp() { return bloodGrp; }
    int getHeight() { return height; }
    int getAge() { return age; }
    int getMR() { return MR_num; }
    float getWeight() { return weight; }
};