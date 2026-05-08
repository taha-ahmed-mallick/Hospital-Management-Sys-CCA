#pragma once

#include <string>
using namespace std;

class Person
{
protected:
    string name, email, phone, password;
    int age;
public:
    virtual void abstarct(void) = 0;
};