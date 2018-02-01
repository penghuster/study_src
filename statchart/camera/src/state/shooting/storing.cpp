#include <iostream>
#include "storing.hpp"

#include "../notshooting/notshooting.hpp"
#include "../notshooting/idle.hpp"

using namespace std;

Storing::Storing()
{
    cout << "Enter Storing" << endl;
}

Storing::~Storing()
{
    cout << "Exit Storing" << endl;
}

string Storing::getStateName() const 
{
    return string("Storing");
}

result Storing::react(const EvStored & evStored)
{
    cout << "Storing::react(const EvStored & evStored)" << endl;
    return transit< NotShooting >();
}

result Storing::react(const EvShutterRelease & evShutterRelease)
{
    cout << "Storing::react(const EvShutterRelease & EvShutterRelease)" << endl;
    cout << "Discard EvShutterRelease" << endl;
    return discard_event();
}
