#pragma once 

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/deferral.hpp>
#include <boost/mpl/list.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"


#include "shooting.hpp"

using namespace boost::statechart;

class Storing : public simple_state< Storing, Shooting >, public IState
{
    public:
        typedef boost::mpl::list<
            custom_reaction< EvStored >, 
            custom_reaction< EvShutterRelease > > reactions;

        Storing();
        ~Storing();
        virtual string getStateName() const;
        result react(const EvStored & evStored);
        result react(const EvShutterRelease & evShutterRelease);
};
