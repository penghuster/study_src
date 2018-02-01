#include <iostream>

#include "shooting.hpp"
#include "../notshooting/notshooting.hpp"
#include "../notshooting/idle.hpp"

using namespace std;


Shooting::Shooting()
{
    cout << "Enter Shooting" << endl;
}

Shooting::~Shooting()
{
    cout << "Exit Shooting" << endl;
}

string Shooting::getStateName() const 
{
    return string("Shooting");
}

result Shooting::react(const EvShutterRelease & evShutterRelease)
{
    cout << "Shooting::react(const EvShutterRelease & evShutterRelease)" << endl;
    return transit< NotShooting >();
}
