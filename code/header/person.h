#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "./menu.h"
using namespace std;

class Person
{
protected:
    string name, email, phone, password;

public:
    Person(string name, string email, string phone, string password) : name(name), email(email), phone(phone), password(password) {}

    virtual void displayProfile(void) = 0;
    virtual void dashboard(string) = 0;

    string getName() { return name; }
    string getEmail() { return email; }
    string getPhone() { return phone; }
    string getPassword() { return password; }
};