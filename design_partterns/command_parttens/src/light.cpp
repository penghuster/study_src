#include <iostream>
#include "light.h"

using namespace std;

void RCTRL::Light::on()
{
    cout << "light is on." << endl;
}

void RCTRL::Light::off()
{
    cout << "light is off" << endl;
}
