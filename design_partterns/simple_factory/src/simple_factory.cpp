#include "simple_factory.h"
#include "cheese_pizza.h"

using namespace std;

factory::Pizza* factory::SimpleFactory::createPizza(PIZZA_TYPE type)
{
    switch(type)
    {
    case CHEESE:
        return new CheesePizza();
    case GREEK:
        return NULL;
    case CLAM:
        return NULL;
    default:
        cout << "Don't recognize type." << endl;
    }
}
