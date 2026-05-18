#pragma once

#include "./person.h"
#include "./files.h"

class Patient : public Person, public FileManage
{
protected:
    // patients attributes
    char gender;
    string bloodGrp;
    int height, age, MR_num, weight;

public:
    Patient(string name, string email, string phone, string password, int age, char gender, string bloodGrp, int height, int weight, int MR_num) : Person(name, email, phone, password), gender(gender), bloodGrp(bloodGrp), height(height), weight(weight), MR_num(MR_num), age(age) {}

    void dashboard(string banner) override
    {
        vector<string> opt = {"Book Appointment",
                              "View Profile",
                              "View Medical History",
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
                bookAppointment(banner);
                break;
            case 1:
                displayProfile(banner);
                break;
            case 2:
                medHistory(banner);
                break;
            case 3:
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
        cout << banner << "\e[1;32m--- Patient Profile ---\e[0m\n";
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Blood Group: " << bloodGrp << endl;
        cout << "Height: " << height << " cm\n";
        cout << "Weight: " << weight << " kg\n";
        cout << "\e[1m\nPress Enter to go back...\e[0m";
        cin.get(); // screen not removed until enter pressed.
    }

    void bookAppointment(string banner)
    {
        Utils::clear();
        cout << banner + "\e[1;32mBook an Appointment\e[0m\n\n";
        cout << "Doctors available in the hospital:\n\n";
        vector<DocStruct> docs = getAllDocs();
        if (docs.size() == 0)
        {
            cout << "\n\e[1;31mDoctors not available in the system\e[0m\n";
            cout << "\e[1m\nPress Enter to go back...\e[0m";
            cin.get();
            return;
        }

        cout << "\e[1;36mID\tName\tSpecialization\tQualification\e[0m\n";
        for (int i = 0; i < docs.size(); i++)
            cout << docs[i].ID << ".\t" << docs[i].name << "\t" << docs[i].specialization << "\t" << docs[i].qualification << endl;
        cout << "\nEnter the ID of the doctor you want to book an appointment with: ";
        int select;
        cin >> select;
        cin.ignore();
        if (select <= 0 || select > docs.size())
            return;
        select--;
        int docID = docs[select].ID;
        vector<int> avail = getAvailibility(docID);
        vector<int> appointments = viewAppointments(docID);
        vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        Utils::clear();
        cout << banner + "\e[1;32mBook an Appointment\e[0m\n\n";
        cout << "Availibility of Dr. " << docs[select].name << ":\n\n";
        for (int i = 0; i < 7; i++)
            cout << i + 1 << ". " << days[i] << ": " << appointments[i] << " / " << avail[i] << " appointment(s) available\n";
        cout << "\nEnter the day you want to book an appointment: ";
        cin >> select;
        cin.ignore();
        if (select <= 0 || select > 7)
            return;
        select--;
        if (avail[select] > appointments[select])
        {
            appointments[select]++;
            addAppointment(docID, appointments, MR_num, select);
            cout << "\n\e[1;32mAppointment booked successfully for " << days[select] << "!!\e[0m\n";
        }
        else
            cout << "\n\e[1;31mSorry, no slots available for " << days[select] << "!!\e[0m\n";
        cout << "\nPress Enter to go back...";
        cin.get();
    }

    void medHistory(string banner)
    {
        Utils::clear();
        cout << banner << "\e[1;32m--- Medical History ---\e[0m\n";
        const vector<MedHistory> history = getHistory(MR_num);
        if (history.size() == 0)
            cout << "\n\e[1;31mNo medical history found!!\e[0m\n";
        else
            for (int i = history.size() - 1; i >= 0; i--)
            {
                cout << "\e[1;36mDate:\e[0m " << history[i].date << endl;
                cout << "\e[1;36mDoctor:\e[0m " << history[i].doctor << endl;
                cout << "\e[1;36mSymptoms:\e[0m " << history[i].symptoms << endl;
                cout << "\e[1;36mPrescription:\e[0m " << history[i].prescription << endl;
                cout << "-----------------------------------\n";
            }
        cout << "\e[1m\nPress Enter to go back...\e[0m";
        cin.get();
    }
};