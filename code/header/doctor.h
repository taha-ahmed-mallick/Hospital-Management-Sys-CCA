#pragma once

#include "./person.h"

class Doctor : public Person
{
protected:
    string specialization;
    long ID;
public:
};