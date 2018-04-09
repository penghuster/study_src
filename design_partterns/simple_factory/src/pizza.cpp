#include <iostream>
#include "pizza.h"

using namespace std;

void factory::Pizza::bake()
{
    cout << "bake pizza" << endl;
}


void factory::Pizza::cut()
{
    cout << "cut pizza" << endl;
}

void factory::Pizza::box()
{
    cout << "box pizza" << endl;
}
