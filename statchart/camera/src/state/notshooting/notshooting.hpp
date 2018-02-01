#pragma once 

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include "../istate.hpp"
#include "../../event/events.hpp"

//NotShooting 是相机的初始状态，且 Camera是 NotShooting的上下文。
//所以，1、定义Camera时需要前置申明 NotShooting, 参见 camera.hpp
//2、当定义NotShooting时，需要Camera的完全定义，故此处包含camera.hpp
#include "../../camera/camera.hpp"

using namespace boost::statechart;

class Idle;

class NotShooting : public simple_state< NotShooting, Camera, Idle>, public IState
{
    public:
        typedef custom_reaction< EvShutterHalf > reactions;

        NotShooting();
        ~NotShooting();

        virtual string getStateName() const;
        result react(const EvShutterHalf &evShutterHalf);
};
