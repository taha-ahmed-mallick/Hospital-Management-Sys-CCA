#pragma once

#include "./person.h"
#include "./files.h"

class Doctor : public Person, public FileManage
{
protected:
    // doctors attributes
    string specialization, qualification;
    int ID;

public:
    Doctor(string name, string email, string phone, string password, string specialization, string qualification, int ID) : Person(name, email, phone, password), specialization(specialization), qualification(qualification), ID(ID) {}

    void dashboard(string banner) override
    {
        vector<string> opt = {"Check Patient",
                              "View Schedule",
                              "Change Availibility",
                              "View Profile",
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
                checkPatient(banner);
                break;
            case 1:
                viewSchedule(banner);
                break;
            case 2:
                changeAvailibility(banner);
                break;
            case 3:
                displayProfile(banner);
                break;
            case 4:
                return;
                break;
            default:
                break;
            }
        }
    }

    void displayProfile(string banner) override
    {
        Utils::clear();
        cout << banner << "\e[1;32m--- Doctor Profile ---\e[0m\n";
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Specialization: " << specialization << endl;
        cout << "Qualification: " << qualification << endl;
        cout << "Doctor ID: " << ID << endl;
        cout << "\e[1m\nPress Enter to go back...\e[0m";
        cin.get();
    }

    void checkPatient(string banner)
    {
        Utils::clear();
        int day = initializeData();
        vector<int> appointments = viewAppointments(ID);
        int todayApp = appointments[day];
        int patMR = getPatAppMR(ID, day);
        if (todayApp == 0 || patMR == 0)
        {
            cout << banner + "\e[1;32mNo appointments for today!!\e[0m\n";
            cout << "\e[1m\nPress Enter to go back...\e[0m";
            cin.get();
            return;
        }
        decAppointment(ID, day);
        PatStruct pat = getPatInfo(patMR);
        cout << banner << "\e[1;32mPatient Name: " << pat.name << "\e[0m\n";
        cout << "MR#: " << patMR << "\tAge: " << pat.age << "\tGender: " << pat.gender << "\tBlood Group: " << pat.bloodGrp << "\tHeight: " << pat.height << "cm\tWeight: " << pat.weight << "kg\n";
        string date, symptoms, prescription;
        cout << "Date: ";
        getline(cin, date);
        cout << "Enter patient's symptoms: ";
        getline(cin, symptoms);
        cout << "Enter your prescription: ";
        getline(cin, prescription);
        appendPrescription(patMR, date, qualification + ". " + name, symptoms, prescription);
        cout << "\e[1;32m\nPrescription added successfully!!\e[0m\n";
        cout << "\e[1m\nPress Enter to go back...\e[0m";
        cin.get();
    }

    void viewSchedule(string banner)
    {
        vector<int> total = getAvailibility(ID);
        vector<int> appointments = viewAppointments(ID);
        vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        Utils::clear();
        string heading = banner + "\e[1;32mYour Schedule\e[0m\n\n";
        cout << heading;
        for (int i = 0; i < 7; i++)
            cout << days[i] << ": " << appointments[i] << " / " << total[i] << " patient(s) appointed\n";
        cout << "\e[1m\nPress Enter to go back...\e[0m";
        cin.get();
    }

    void changeAvailibility(string banner)
    {
        vector<string> opt = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        vector<int> flags(opt.size(), 0);
        string heading = banner + "\e[1;32mChange Availibility\e[0m\n";
        int select = Menu::full(opt, flags, heading);
        Utils::clear();
        cout << heading;
        cout << "Chnage availibility for " << opt[select] << "\n\n";
        vector<int> avail = getAvailibility(ID);
        vector<int> appointments = viewAppointments(ID);
        cout << "Enter number of patients: ";
        cin >> avail[select];
        if (avail[select] < appointments[select])
        {
            avail[select] = appointments[select];
            cout << "\n\e[1;31mYou have " << appointments[select] << " appointment(s) already booked for " << opt[select] << ". You can't set availibility less than that.\e[0m\n";
        }
        else if (avail[select] < 0)
        {
            avail[select] = 0;
            cout << "\n\e[1;31mInvalid input. Availibility can't be negative.\e[0m\n";
        }
        updateAvailibility(ID, avail);
        cout << "\e[1;32m\nAvailibility updated successfully to " << avail[select] << "!!\e[0m\e[1m\nPress Enter to go back...\e[0m";
        cin.ignore();
        cin.get();
    }
};