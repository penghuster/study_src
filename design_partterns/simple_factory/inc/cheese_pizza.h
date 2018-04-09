#pragma once 

#include "pizza.h"
#include <string>

namespace factory
{

    class CheesePizza : public Pizza
    {
    private:
        string name;
        string dough;
        string sauce;

    public:
        virtual void prepare();
        void bake();
        void cut();
        void box();

    };

}
