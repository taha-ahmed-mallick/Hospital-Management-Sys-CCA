#pragma once

#include "./person.h"

class Patient : public Person
{
protected:
    string gender, bloodGrp;
    int height, weight;
    long MR_num;
public:
};