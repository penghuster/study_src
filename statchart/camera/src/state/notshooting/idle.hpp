#pragma once 

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include "../istate.hpp"
#include "../../event/events.hpp"

//Idle 是NotShooting的初始化状态，Notshooting 是 Idle的上下文，所以
//1、当定义Notshooting时，需要前置声明 Idle
//2、定义Idle时则需要Notshooting的全定义
#include "notshooting.hpp"

using namespace boost::statechart;

class Idle : public simple_state< Idle, NotShooting>, public IState
{
    public:
        typedef custom_reaction< EvConfig > reactions;

        Idle();
        ~Idle();
        virtual string getStateName() const;
        result react(const EvConfig & evConfig);
};
 
