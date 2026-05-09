#pragma once

#include "./person.h"
#include "./auth.h"

class Doctor : public Person
{
protected:
    string specialization;
    int ID;

public:
    Doctor(string name, string email, string phone, string password, string specialization, int ID) : Person(name, email, phone, password), specialization(specialization), ID(ID) {}

    void displayProfile()
    {
        cout << "Specialization: " << specialization << endl;
    }
};