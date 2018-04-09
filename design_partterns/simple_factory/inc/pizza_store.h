#pragma once 
#include "common_def.h"

namespace factory{

class Pizza;
class SimpleFactory;

class PizzaStore
{
private:
    SimpleFactory *factory;

public:
    PizzaStore(SimpleFactory *fac);
    ~PizzaStore();
    Pizza* orderPizza(PIZZA_TYPE type);

};

}
