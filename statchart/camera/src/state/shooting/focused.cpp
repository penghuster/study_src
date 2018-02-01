#include <iostream>

#include "focused.hpp"
#include "storing.hpp"
#include "../../camera/camera.hpp"

using namespace std;

Focused :: Focused()
{
    cout << "Enter Focused" << endl;
}

Focused :: ~Focused()
{
    cout << "Exit Focused" << endl;
}

string Focused::getStateName() const 
{
    return string("Focused");
}

result Focused::react(const EvShutterFull & evShutterFull)
{
    cout << "Focused::react(const EvShutterFull & evShutterFull)" << endl;
    if(context< Camera >().isMemAvail() )
    {
        cout << "Guard: isMemAvail() is true" << endl;
        return transit< Storing >(&Camera::allocMem, evShutterFull);
    }
    else
    {
        cout << "Guard: isMemAvail() is false" << endl;
        return discard_event();
    }
}
