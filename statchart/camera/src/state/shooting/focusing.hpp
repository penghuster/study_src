#pragma once 

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>
#include <boost/statechart/deferral.hpp>

#include "../../event/events.hpp"
#include "../istate.hpp"

#include "shooting.hpp"

class Focusing : public simple_state< Focusing, Shooting >, public IState
{
    public:
        //如果在相机处于focusing状态，对焦还未完成，用户按压 shutter 按钮，我们将此事件延迟到对焦完成后
        //这意味着：
        //当 EvShutterFull 事件到来时：
        //复制 Evshutterfull事件通过copy构造函数
        //放此事件到一个独立的队列中，析构此 Evshutterfull 事件
        typedef boost::mpl::list< custom_reaction< EvInFocus >, deferral< EvShutterFull > > reactions;

        Focusing();
        ~Focusing();
        virtual string getStateName() const;
        result react(const EvInFocus &evInFocu);
};
