#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include "./doctor.h"
#include "./patient.h"
using namespace std;
typedef struct
{
    int docID, MR;
} IDs;

class FileManage
{
public:
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

    static void createDoc(Doctor *doc)
    {
        char buffer[32];
        sprintf(buffer, "DOC%06d.txt", doc->getID());
        string fileName(buffer);
        ofstream docFile("./records/doctors/" + fileName);
        string data = doc->getName() + "|" + doc->getEmail() + "|" + doc->getPhone() + "|" + doc->getPassword() + "|" + doc->getSpec() + "|" + doc->getQuali() + "|" + to_string(doc->getID());
        docFile << data;
        docFile.close();
    }

    static void createPat(Patient *pat)
    {
        char buffer[32];
        sprintf(buffer, "PAT%06d.txt", pat->getMR());
        string fileName(buffer);
        ofstream patFile("./records/patients/" + fileName);
        string data = pat->getName() + "|" + pat->getEmail() + "|" + pat->getPhone() + "|" + pat->getPassword() + "|" + to_string(pat->getAge()) + "|" + string(1, pat->getGender()) + "|" + pat->getBloodGrp() + "|" + to_string(pat->getHeight()) + "|" + to_string(pat->getWeight()) + "|" + to_string(pat->getMR());
        patFile << data;
        patFile.close();
    }

    static Patient *getPat(string MR, string pass)
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
        Patient *patient = new Patient(name, email, phone, password, age, gender, bloodGrp, height, (float)weight, ID);
        return patient;
    }

    static Doctor *getDoc(string ID, string pass) {
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
        Doctor *doctor = new Doctor(name, email, phone, password, specialization, qualification, docID);
        return doctor;
    }
};