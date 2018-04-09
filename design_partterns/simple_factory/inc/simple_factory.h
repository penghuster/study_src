#pragma once 

#include "common_def.h"
//#include "pizza.h"

namespace factory
{
    class Pizza;



    class SimpleFactory
    {
    public:
        Pizza* createPizza(PIZZA_TYPE type );
        
    };

}
