#include "cheese_pizza.h"
#include "simple_factory.h"
#include "pizza_store.h"

factory::PizzaStore::PizzaStore(SimpleFactory* fac)
{
    factory = fac;
}

factory::PizzaStore::~PizzaStore()
{
}

factory::Pizza* factory::PizzaStore::orderPizza(PIZZA_TYPE type)
{
    Pizza *pizza = factory->createPizza(type);
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;

}
