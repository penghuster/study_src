#pragma once

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/transition.hpp>

#include "../istate.hpp"
#include "../../event/events.hpp"

#include "../../camera/camera.hpp"

using namespace boost::statechart;

class Focusing;

class Shooting : public simple_state<Shooting, Camera, Focusing>, public IState
{
    public:
        typedef custom_reaction< EvShutterRelease > reactions;

        Shooting();
        virtual ~Shooting();
        virtual string getStateName() const;
        result react(const EvShutterRelease & evShutterRelease);
};

