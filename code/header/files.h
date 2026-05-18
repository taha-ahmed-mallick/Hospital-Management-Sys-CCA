#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

typedef struct
{
    int docID, MR;
} IDs;

typedef struct
{
    int ID;
    string name, email, phone, password, specialization, qualification;
} DocStruct;

typedef struct
{
    int MR;
    string name, email, phone, password, bloodGrp;
    char gender;
    int age, height, weight;
} PatStruct;

typedef struct
{
    string date, doctor, symptoms, prescription;
} MedHistory;

class FileManage
{
protected:
    // fetches availibility of a doctor from his file and returns it as a vector of integers
    vector<int> getAvailibility(int docID)
    {
        vector<int> avail;
        vector<string> lines;
        char buffer[32];
        sprintf(buffer, "DOC%06d.txt", docID);
        string fileName(buffer), line;
        ifstream doc("./records/doctors/" + fileName);
        while (getline(doc, line))
            lines.push_back(line);
        for (int i = 0; i < lines.size(); i++)
            if (lines[i] == "│")
            {
                for (int j = i + 1; j < lines.size() && lines[j] != "│"; j++)
                    avail.push_back(stoi(lines[j]));
                break;
            }
        doc.close();
        return avail;
    }

    // updates the availibility of a doctor in his file using the given vector of integers
    void updateAvailibility(int docID, vector<int> avail)
    {
        vector<string> lines;
        char buffer[32];
        sprintf(buffer, "DOC%06d.txt", docID);
        string fileName(buffer), line;
        ifstream doc("./records/doctors/" + fileName);
        while (getline(doc, line))
            lines.push_back(line);
        doc.close();
        for (int i = 0; i < lines.size(); i++)
            if (lines[i] == "│")
            {
                for (int j = i + 1; j < lines.size() && lines[j] != "│"; j++)
                    lines[j] = to_string(avail[j - i - 1]);
                break;
            }
        ofstream out("./records/doctors/" + fileName);
        for (string line : lines)
            out << line << endl;
        out.close();
    }

    // fetches the number of appointments a doctor has on each day and returns it as a vector of integers
    vector<int> viewAppointments(int docID)
    {
        vector<int> appointments;
        vector<string> lines;
        char buffer[32];
        sprintf(buffer, "DOC%06d.txt", docID);
        string fileName(buffer), line;
        ifstream doc("./records/doctors/" + fileName);
        while (getline(doc, line))
            lines.push_back(line);
        for (int i = 10; i < 17; i++)
            appointments.push_back(stoi(lines[i]));
        doc.close();
        return appointments;
    }

    // decreases the number of appointments for a doctor on a specific day by 1 in his file
    void decAppointment(int docID, int day)
    {
        vector<string> lines;
        char buffer[32];
        sprintf(buffer, "DOC%06d.txt", docID);
        string fileName(buffer), line;
        ifstream doc("./records/doctors/" + fileName);
        while (getline(doc, line))
            lines.push_back(line);
        int decrement = stoi(lines[10 + day]) - 1;
        lines[10 + day] = to_string(decrement);
        doc.close();
        ofstream out("./records/doctors/" + fileName);
        for (string line : lines)
            out << line << endl;
        out.close();
    }

    // adds an appointment for a doctor on a specific day in his file and adds the doctor and day to the patient's file using the given medical record number
    void addAppointment(int docID, vector<int> appointments, int MR, int day)
    {
        vector<string> lines;
        char buffer[32];
        sprintf(buffer, "DOC%06d.txt", docID);
        string fileName(buffer), line;
        ifstream doc("./records/doctors/" + fileName);
        while (getline(doc, line))
            lines.push_back(line);
        for (int i = 10; i < 17; i++)
            lines[i] = to_string(appointments[i - 10]);
        doc.close();
        ofstream out("./records/doctors/" + fileName);
        for (string line : lines)
            out << line << endl;
        out.close();
        sprintf(buffer, "PAT%06d.txt", MR);
        fileName = buffer;
        ifstream data("./records/patients/" + fileName);
        lines.clear();
        while (getline(data, line))
            lines.push_back(line);
        for (int i = 0; i < lines.size(); i++)
            if (lines[i] == "│")
            {
                lines.insert(lines.begin() + i + 1, to_string(docID) + "|" + to_string(day));
                break;
            }
        data.close();
        ofstream patFile("./records/patients/" + fileName);
        for (string line : lines)
            patFile << line << endl;
        patFile.close();
    }

    // fetches the first patient it finds from ./records/patients/ who has appointment of that doctor
    int getPatAppMR(int docID, int dayIn)
    {
        int MR = 0;
        char buffer[32];
        for (int i = 1;; i++)
        {
            vector<string> lines;
            sprintf(buffer, "PAT%06d.txt", i);
            string fileName = buffer, line;
            ifstream pat("./records/patients/" + fileName);
            if (!pat)
                break;
            while (getline(pat, line))
                lines.push_back(line);
            for (int k = 0; k < lines.size(); k++)
                if (lines[k] == "│")
                {
                    for (int j = k + 1; j < lines.size() && lines[j] != "│"; j++)
                    {
                        stringstream ss(lines[j]);
                        string temp;
                        int dID = 0, day;
                        getline(ss, temp, '|');
                        dID = stoi(temp);
                        getline(ss, temp, '|');
                        day = stoi(temp);
                        if (dID == docID && day == dayIn)
                        {
                            MR = i;
                            lines.erase(lines.begin() + j);
                            pat.close();
                            ofstream patFile("./records/patients/" + fileName);
                            for (string line : lines)
                                patFile << line << endl;
                            patFile.close();
                            return MR;
                        }
                    }
                    break;
                }
        }
        return MR;
    }

    // fetches the medical history of a patient from his file and returns it as a vector of MedHistory objects
    vector<MedHistory> getHistory(int MR)
    {
        char buffer[32];
        sprintf(buffer, "PAT%06d.txt", MR);
        string fileName(buffer), line;
        ifstream pat("./records/patients/" + fileName);
        vector<string> lines;
        vector<MedHistory> history;
        while (getline(pat, line))
            lines.push_back(line);
        int count = 0;
        for (int i = 0; i < lines.size(); i++)
            if (lines[i] == "│")
                count++;
            else if (count == 2)
            {
                stringstream ss(lines[i]);
                string date, doctor, symptoms, prescription;
                getline(ss, date, '|');
                getline(ss, doctor, '|');
                getline(ss, symptoms, '|');
                getline(ss, prescription, '|');
                history.push_back({date, doctor, symptoms, prescription});
            }
        pat.close();
        return history;
    }

    // Gets all the doctors from ./records/doctors/ and returns them as a vector of DocStruct objects
    vector<DocStruct> getAllDocs()
    {
        vector<DocStruct> doctors;
        char buffer[32];
        string fileName, line;
        for (int i = 1;; i++)
        {
            sprintf(buffer, "DOC%06d.txt", i);
            fileName = buffer;
            ifstream doc("./records/doctors/" + fileName);
            if (!doc)
                break;
            getline(doc, line);
            stringstream ss(line);
            string name, temp, specialization, qualification, input;
            int docID;
            getline(ss, name, '|');
            getline(ss, temp, '|');
            getline(ss, temp, '|');
            getline(ss, temp, '|');
            getline(ss, specialization, '|');
            getline(ss, qualification, '|');
            getline(ss, input, '|');
            docID = stoi(input);
            doctors.push_back({docID, name, "", "", "", specialization, qualification});
            doc.close();
        }
        return doctors;
    }

    // fetches the information of a patient using his medical record number and returns it as a PatStruct object
    PatStruct getPatInfo(int MR)
    {
        char buffer[32];
        sprintf(buffer, "PAT%06d.txt", MR);
        string fileName(buffer), line;
        ifstream pat("./records/patients/" + fileName);
        if (!pat)
            throw string("\n\e[1;31mPatient with MR#" + to_string(MR) + " doesn't exists\e[0m\n");
        getline(pat, line);
        stringstream ss(line);
        string name, bloodGrp, input, temp;
        int age, height, weight;
        char gender;
        getline(ss, name, '|');
        getline(ss, temp, '|');
        getline(ss, temp, '|');
        getline(ss, temp, '|');
        getline(ss, input, '|');
        age = stoi(input);
        getline(ss, input, '|');
        gender = input[0];
        getline(ss, bloodGrp, '|');
        getline(ss, input, '|');
        height = stoi(input);
        getline(ss, input, '|');
        weight = stoi(input);
        pat.close();
        PatStruct patient = {MR, name, "", "", "", bloodGrp, gender, age, height, weight};
        return patient;
    }

    // Appends a prescription to the patient's file using the given medical record number, date, doctor, symptoms and prescription
    void appendPrescription(int MR, string date, string doctor, string symptoms, string prescription)
    {
        char buffer[32];
        sprintf(buffer, "PAT%06d.txt", MR);
        string fileName(buffer), line;
        ofstream pat("./records/patients/" + fileName, ios::app);
        pat << date << "|" << doctor << "|" << symptoms << "|" << prescription << endl;
        pat.close();
    }

public:
    // fetches the last used doctor ID and medical record number from ./records/data.txt and returns them as an IDs struct
    static IDs getIDs()
    {
        ifstream data("./records/data.txt");
        string line, input;
        int lastMR, lastID;
        data >> line;
        stringstream ss(line);
        getline(ss, input, '|');
        lastID = stoi(input);
        getline(ss, input, '|');
        lastMR = stoi(input);
        data.close();
        IDs both;
        both.docID = lastID;
        both.MR = lastMR;
        return both;
    }

    // updates the last used doctor ID and medical record number in ./records/data.txt using the given IDs struct
    static void updateIDs(IDs both)
    {
        vector<string> lines;
        string temp, replace = to_string(both.docID) + "|" + to_string(both.MR);
        ifstream data("./records/data.txt");
        while (getline(data, temp))
            lines.push_back(temp);
        data.close();
        ofstream out("./records/data.txt");
        lines[0] = replace;
        out.seekp(0);
        for (string line : lines)
            out << line << endl;
        out.close();
    }

    // fetches the current day from ./records/data.txt and returns it as an integer from 0 to 6 representing the days of the week
    static int initializeData()
    {
        int today = 0;
        ifstream data("./records/data.txt");
        if (!data)
        {
            ofstream data("./records/data.txt");
            data << "0|0\n0";
            data.close();
        }
        else
        {
            string line;
            getline(data, line);
            getline(data, line);
            data.close();
            char day = line[0];
            today = day - '0';
        }
        return today;
    }

    // updates the day in data.txt
    static void updateDay()
    {
        vector<string> lines;
        string line;
        ifstream data("./records/data.txt");
        while (getline(data, line))
            lines.push_back(line);
        data.close();
        ofstream out("./records/data.txt");
        int val = stoi(lines[1]);
        val++;
        if (val > 6)
            val = 0;
        lines[1] = to_string(val);
        out.seekp(0);
        for (string line : lines)
            out << line << endl;
        out.close();
    }

    // creates a new doctor file in ./records/doctors/ using the information in the given DocStruct object
    static void createDoc(DocStruct &doc)
    {
        char buffer[32];
        sprintf(buffer, "DOC%06d.txt", doc.ID); // to format string as per file.
        string fileName(buffer);
        ofstream docFile("./records/doctors/" + fileName);// file open
        string data = doc.name + "|" + doc.email + "|" + doc.phone + "|" + doc.password + "|" + doc.specialization + "|" + doc.qualification + "|" + to_string(doc.ID); //retrive doc id to string
        docFile << data << "\n│\n0\n0\n0\n0\n0\n0\n0\n│\n0\n0\n0\n0\n0\n0\n0\n│";// insertion
        docFile.close();// file close
    }

    // creates a new patient file in ./records/patients/ using the information in the given PatStruct object
    static void createPat(PatStruct &pat)
    {
        char buffer[32];
        sprintf(buffer, "PAT%06d.txt", pat.MR);
        string fileName(buffer);
        ofstream patFile("./records/patients/" + fileName);
        string data = pat.name + "|" + pat.email + "|" + pat.phone + "|" + pat.password + "|" + to_string(pat.age) + "|" + string(1, pat.gender) + "|" + pat.bloodGrp + "|" + to_string(pat.height) + "|" + to_string(pat.weight) + "|" + to_string(pat.MR);
        patFile << data << "\n│\n│\n";
        patFile.close();
    }

    // fetches the information of a patient using his MR and password and returns it as a PatStruct object
    static PatStruct getPat(string MR, string pass)
    {
        string line;
        ifstream pat("./records/patients/PAT" + MR + ".txt");
        if (!pat)
            throw string("\n\e[1;31mPatient with MR#" + MR + " doesn't exists\e[0m\n");
        getline(pat, line);
        stringstream ss(line);
        string name, email, phone, password, bloodGrp, input;
        int age, height, weight, ID;
        char gender;
        getline(ss, name, '|');
        getline(ss, email, '|');
        getline(ss, phone, '|');
        getline(ss, password, '|');
        if (pass != password)
            throw string("\n\e[1;31mInvalid password!!\e[0m\n");
        getline(ss, input, '|');
        age = stoi(input);
        getline(ss, input, '|');
        gender = input[0];
        getline(ss, bloodGrp, '|');
        getline(ss, input, '|');
        height = stoi(input);
        getline(ss, input, '|');
        weight = stoi(input);
        getline(ss, input, '|');
        ID = stoi(input);
        PatStruct patient = {ID, name, email, phone, password, bloodGrp, gender, age, height, weight};
        return patient;
    }

    // fetches the information of a doctor using his ID and password and returns it as a DocStruct object
    static DocStruct getDoc(string ID, string pass)
    {
        string line;
        ifstream doc("./records/doctors/DOC" + ID + ".txt");
        if (!doc)
            throw string("\n\e[1;31mDoctor with ID: " + ID + " doesn't exists\e[0m\n");
        getline(doc, line);
        stringstream ss(line);
        string name, email, phone, password, specialization, qualification, input;
        int docID;
        getline(ss, name, '|');
        getline(ss, email, '|');
        getline(ss, phone, '|');
        getline(ss, password, '|');
        if (pass != password)
            throw string("\n\e[1;31mInvalid password!!\e[0m\n");
        getline(ss, specialization, '|');
        getline(ss, qualification, '|');
        getline(ss, input, '|');
        docID = stoi(input);
        DocStruct doctor = {docID, name, email, phone, password, specialization, qualification};
        return doctor;
    }
};