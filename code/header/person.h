#pragma once

#include <string>
using namespace std;

class Person
{
protected:
    string name;
    int age;
public:
    virtual void abstarct(void) = 0;
};