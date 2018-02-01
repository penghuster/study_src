#pragma once 

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/termination.hpp>
#include <boost/statechart/transition.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

//NotShooting 是Configuring的上下文，故Notshooting的全定义需要包含
#include "notshooting.hpp"

//Idle的全定义在此处需要
#include "idle.hpp"

using namespace boost::statechart;

class Configuring : public simple_state< Configuring, NotShooting>, public IState
{
    public:
        //a short way for:
        //typedef custom_reaction< EvConfig > reactions;
        //result react(const EvConfig &evConfig)
        //{
        //  return transit< Idle >( &Camera::PowerSavingMode, evConfig );
        //}
        typedef transition< EvConfig, Idle, Camera, &Camera::powerSavingMode > reactions;

        Configuring();
        ~Configuring();
        virtual string getStateName() const;
};


