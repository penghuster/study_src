#include <iostream>
#include <boost/msm/back/state_machine.hpp>
 
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
 
namespace
{
    namespace msm = boost::msm;
    namespace msmf = boost::msm::front;
    namespace mpl = boost::mpl;
 
    // ----- Events
    struct EventMCU {};
    struct EventSMS {};
    struct EventCall{};

    struct EventWrkToStby{};
    struct EventStbyToSubSleep {};
    struct EventSubWrkToSubSleep{};
    struct EventSubWrkToSleep{};

         
    // ----- State machine
    struct TemSm_:msmf::state_machine_def<TemSm_>
    {
        // InitStates
        struct Init:msmf::state<> {};
        
        //Choices
        struct Choice_:msmf::state<>{};
        
        //Working
        struct Working:msmf::state<> 
        {
            // Entry action
            template <class Event,class Fsm>
            void on_entry(Event const&, Fsm&) 
            {
                std::cout << "Working::on_entry()" << std::endl;
            }
            // Exit actions
            template <class Event,class Fsm>
            void on_exit(Event const&, Fsm&) 
            {
                std::cout << "Working::on_exit()" << std::endl;
            }
        };       

        //standby
        struct Standby:msmf::state<> 
        {
            // Entry action
            template <class Event,class Fsm>
            void on_entry(Event const&, Fsm&) 
            {
                std::cout << "Standby::on_entry()" << std::endl;
            }
            // Exit actions
            template <class Event,class Fsm>
            void on_exit(Event const&, Fsm&) 
            {
                std::cout << "Standby::on_exit()" << std::endl;
            }
        };       

        //Sleeping
        struct Sleeping:msmf::state<> 
        {
            // Entry action
            template <class Event,class Fsm>
            void on_entry(Event const&, Fsm&) 
            {
                std::cout << "Sleeping::on_entry()" << std::endl;
            }
            // Exit actions
            template <class Event,class Fsm>
            void on_exit(Event const&, Fsm&) 
            {
                std::cout << "Sleeping::on_exit()" << std::endl;
            }
        };       

        struct SleepPoll_:msmf::state_machine_def<SleepPoll_>
        {

            // Entry action
            template <class Event,class Fsm>
            void on_entry(Event const&, Fsm&) 
            {
                BOOST_STATIC_ASSERT((boost::is_convertible<Fsm, TemSm_>::value));
                std::cout << "SleepPoll::on_entry()" << std::endl;
            }
            // Exit actions
            template <class Event,class Fsm>
            void on_exit(Event const&, Fsm&) 
            {
                BOOST_STATIC_ASSERT((boost::is_convertible<Fsm, TemSm_>::value));
                std::cout << "SleepPoll::on_exit()" << std::endl;
            }

            //SubSleep
            struct SubSleep:msmf::state<> 
            {
                // Entry action
                template <class Event,class Fsm>
                void on_entry(Event const&, Fsm&) 
                {
                    BOOST_STATIC_ASSERT((boost::is_convertible<Fsm, SleepPoll_>::value));
                    std::cout << "SubSleep::on_entry()" << std::endl;
                }
                // Exit actions
                template <class Event,class Fsm>
                void on_exit(Event const&, Fsm&) 
                {
                    BOOST_STATIC_ASSERT((boost::is_convertible<Fsm, SleepPoll_>::value));
                    std::cout << "SubSleep::on_exit()" << std::endl;
                }
            };

            //Sleeping
            struct SubWork:msmf::state<> 
            {
                // Entry action
                template <class Event,class Fsm>
                void on_entry(Event const&, Fsm&) 
                {
                    BOOST_STATIC_ASSERT((boost::is_convertible<Fsm, SleepPoll_>::value));
                    std::cout << "SubWork::on_entry()" << std::endl;
                }
                // Exit actions
                template <class Event,class Fsm>
                void on_exit(Event const&, Fsm&) 
                {
                    BOOST_STATIC_ASSERT((boost::is_convertible<Fsm, SleepPoll_>::value));
                    std::cout << "SubWork::on_exit()" << std::endl;
                }
            };       

            struct Entry:msmf::entry_pseudo_state<> {}; 
            struct ExitRTC:msmf::exit_pseudo_state< EventSubWrkToSleep > {};
            struct ExitSMS:msmf::exit_pseudo_state< EventSMS > {};
            struct ExitCall:msmf::exit_pseudo_state< EventCall > {};

            typedef mpl::vector<SubWork> initial_state;

            struct transition_table:mpl::vector<
                                    msmf::Row< Entry, boost::any, SubSleep, msmf::none, msmf::none >,
                                    msmf::Row< SubWork, EventSubWrkToSubSleep, SubSleep, msmf::none, msmf::none >,
                                    msmf::Row< SubWork, EventSubWrkToSleep, ExitRTC, msmf::none, msmf::none >,
                                    msmf::Row< SubWork, EventCall, ExitCall, msmf::none, msmf::none >,
                                    msmf::Row< SubWork, EventSMS, ExitSMS, msmf::none, msmf::none >
                                    >{};
            
        };
        // Set initial SourceState
        typedef Init initial_state;                                                     

        typedef msm::back::state_machine<SleepPoll_> SleepPoll;

        struct GuardCondition
        {
            template <class Event, class Fsm, class SourceState, class TargetState>
            bool operator()(Event const&, Fsm& f, SourceState&, TargetState&) const
            {
                if(1 == f.condition)    return true;
                return false;
            }
        };
        // Actions
        struct ActionAssign 
        {
            template <class Event, class Fsm, class SourceState, class TargetState>
            void operator()(Event const&, Fsm& f, SourceState&, TargetState&) const
            {
                f.condition = 0;
                std::cout << "ActionAssign()" << std::endl;
            }
        };

        struct  ActionInitToWorking
        {
            template <class Event, class Fsm, class SourceState, class TargetState>
            void operator()(Event const&, Fsm& f, SourceState&, TargetState&) const
            {
                std::cout << "ActionInitToWorking() condition = " << f.condition << std::endl;
            }
        };
        
        struct ActionInitToSleepPoll
        {

            template <class Event, class Fsm, class SourceState, class TargetState>
            void operator()(Event const&, Fsm& f, SourceState&, TargetState&) const
            {
                std::cout << "ActionInitToSleepPoll() condition = " << f.condition << std::endl;
            }
        };
        // Transition transition_table
        struct transition_table:mpl::vector<
                      //Start       Event       Next        Action         Guard
            msmf::Row < Init,    msmf::none, Working,    ActionInitToWorking,    msmf::none >,
            msmf::Row< Working,     EventWrkToStby, Standby, msmf::none,    msmf::none >,
            msmf::Row< Standby,    EventStbyToSubSleep, SleepPoll::entry_pt<SleepPoll_::Entry>, msmf::none, msmf::none>,
            msmf::Row< SleepPoll::exit_pt<SleepPoll_::ExitRTC>, EventSubWrkToSleep, Sleeping, msmf::none, msmf::none>,
            msmf::Row< SleepPoll::exit_pt<SleepPoll_::ExitSMS>, EventSMS, Working, msmf::none, msmf::none>,
            msmf::Row< SleepPoll::exit_pt<SleepPoll_::ExitCall>, EventCall, Working, msmf::none, msmf::none>,
            msmf::Row< SleepPoll,   EventMCU, Working, msmf::none,    msmf::none >

        > {};

        //template <class Event,class Fsm>
        ~TemSm_()
        {
            std::cout << "hello" << std::endl;
        }

        private:
            int condition;
    };

    // Pick a back-end
    typedef msm::back::state_machine<TemSm_> TemSm;
    
    void test() 
    {        
        TemSm sm1;
        sm1.start(); 
        std::cout << "send EventWrkToStby" << std::endl;
        sm1.process_event(EventWrkToStby());
        std::cout << "send EventStbyToSubSleep" << std::endl;
        sm1.process_event(EventStbyToSubSleep());
        //std::cout << "send EventSubWrkToSleep" << std::endl;
       // sm1.process_event(EventSubWrkToSleep());
        //std::cout << "send EventCall" << std::endl;
       // sm1.process_event(EventCall());
        std::cout << "send EventMCU" << std::endl;
        sm1.process_event(EventMCU());
    }

}

int main()
{

    test();

    return 0;
}
