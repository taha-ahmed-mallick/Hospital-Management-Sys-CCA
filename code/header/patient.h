#pragma once

#include "./person.h"
#include "./auth.h"

class Patient : public Person
{
protected:
    char gender;
    string bloodGrp;
    int height, age, MR_num;
    float weight;

public:
    Patient(string name, string email, string phone, string password, int age, char gender, string bloodGrp, int height, float weight, int MR_num) : Person(name, email, phone, password), gender(gender), bloodGrp(bloodGrp), height(height), weight(weight), MR_num(MR_num), age(age) {}

    void displayProfile()
    {
        cout << "Gender: " << gender << endl;
    }
};