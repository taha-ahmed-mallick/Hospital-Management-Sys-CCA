#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "./menu.h"
using namespace std;

class Person
{
protected:
    // common attributes for both doctors and patients
    string name, email, phone, password;

public:
    Person(string name, string email, string phone, string password) : name(name), email(email), phone(phone), password(password) {}

    // abstract class with pvfs for profile and dashboard
    virtual void displayProfile(string) = 0;
    virtual void dashboard(string) = 0;
};