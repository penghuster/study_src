#pragma once 

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

#include "shooting.hpp"

class Focused : public simple_state< Focused, Shooting > , public IState
{
    public:
        typedef custom_reaction< EvShutterFull > reactions;

        Focused();
        ~Focused();
        virtual string getStateName() const;
        result react(const EvShutterFull & evShutterFull);
};


