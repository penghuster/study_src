#pragma once

#include <iostream>
#include <boost/statechart/state_machine.hpp>
#include "../event/events.hpp"

using namespace boost::statechart;
using namespace std;

class NotShooting;

class Camera : public state_machine<Camera, NotShooting>
{
    public:
        Camera();
        ~Camera();

        bool isMemAvail() const;
        bool isBatteryLow() const;

        string getCurState() const;

        //transition action
        void displayFocused(const EvInFocus &evInFocus);
        void allocMem(const EvShutterFull &evShutterFull);
        void powerSavingMode(const EvConfig &evConfig);
};



