/*
All file handling functionalities
Providing classes with useable data in form of
vector
*/

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
        ofstream docFile("./records/patients/" + fileName);
        string data = pat->getName() + "|" + pat->getEmail() + "|" + pat->getPhone() + "|" + pat->getPassword() + "|" + to_string(pat->getAge()) + "|" + to_string(pat->getGender()) + "|" + pat->getBloodGrp() + "|" + to_string(pat->getHeight()) + "|" + to_string(pat->getWeight()) + "|" + to_string(pat->getMR());
        docFile << data;
        docFile.close();
    }
};