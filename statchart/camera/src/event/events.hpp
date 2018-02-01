#pragma once 

#include <boost/statechart/event.hpp>

using namespace boost::statechart;

class EvConfig : public event< EvConfig >
{
    public:
        EvConfig();
        ~EvConfig();
};

class EvShutterHalf : public event< EvShutterHalf >
{
    public:
        EvShutterHalf();
        ~EvShutterHalf();
};

class EvShutterFull : public event< EvShutterFull >
{
    public:
        EvShutterFull();
        ~EvShutterFull();
};

class EvShutterRelease : public event< EvShutterRelease >
{
    public:
        EvShutterRelease();
        ~EvShutterRelease();
};

class EvInFocus : public event< EvInFocus >
{
    public:
        EvInFocus();
        ~EvInFocus();
};

class EvStored : public event< EvStored >
{
    public:
        EvStored();
        ~EvStored();
};
