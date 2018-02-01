#include <iostream>
#include "configuring.hpp"

using namespace std;

Configuring :: Configuring()
{
    cout << "Enter Configuring" << endl;
}

Configuring :: ~Configuring()
{
    cout << "Exit Configuring" << endl;
}

string Configuring :: getStateName() const 
{
    return string("Configuring");
}


