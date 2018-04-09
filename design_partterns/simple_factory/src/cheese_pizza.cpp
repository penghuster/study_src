#include "cheese_pizza.h"

using namespace std;

void factory::CheesePizza::prepare()
{
    cout << "Preparing " << name << endl;
    cout << "Tossing dough" << endl;
}

void factory::CheesePizza::cut()
{
    cout << "cut into five pieces." << endl;
}

void factory::CheesePizza::bake()
{
    cout << "bake for 5 minutes" << endl;
}

void factory::CheesePizza::box()
{
    cout << "place it into offical pizza box."  << endl;
}


