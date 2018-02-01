#pragma once 
#include <string>


struct IState
{
    virtual std::string getStateName() const =0;
};
