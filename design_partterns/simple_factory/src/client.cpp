#include <iostream>
#include "pizza_store.h"
#include "simple_factory.h"
#include "cheese_pizza.h"

using namespace std;
using namespace factory;

int main(int argc, char **argv)
{
    SimpleFactory *fac = new SimpleFactory();
    PizzaStore *store = new PizzaStore(fac);
    Pizza *pz = store->orderPizza(CHEESE);
    delete fac;
    delete store;
    delete pz;
    cout << "hello simple factory." << endl;
}
