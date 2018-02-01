#include <iostream>
#include "focusing.hpp"
#include "focused.hpp"
#include "../../camera/camera.hpp"

using namespace std;

Focusing::Focusing()
{
    cout << "Enter Focusing" << endl;
}

Focusing::~Focusing()
{
    cout << "Exit Focusing" << endl;
}

string Focusing::getStateName() const 
{
    return string("Focusing");
}

result Focusing::react(const EvInFocus & evInFocus)
{
    cout << "Focusing::react(const EvInFocus & evInFocus)" << endl;
    return transit< Focused >(&Camera::displayFocused, evInFocus);
}
