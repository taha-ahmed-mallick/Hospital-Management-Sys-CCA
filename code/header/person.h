#pragma once

#include <iostream>
using namespace std;

class Person
{
protected:
    string name, email, phone, password;

public:
    Person(string name, string email, string phone, string password) : name(name), email(email), phone(phone), password(password) {}

    virtual void displayProfile(void) = 0;
};