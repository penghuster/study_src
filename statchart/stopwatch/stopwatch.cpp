#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <ctime>
#include <iostream>

namespace sc = boost::statechart;

struct EvStartStop : sc::event< EvStartStop > {};
struct EvReset : sc::event< EvReset > {};

struct IElapsedTime
{
    virtual double ElapsedTime() const = 0;
};

struct Active;
struct StopWatch : sc::state_machine< StopWatch, Active > 
{
    double ElapsedTime() const 
    {
        return state_cast< const IElapsedTime &>().ElapsedTime();
    }
};

struct Stopped;

// simple_state 类模板最多可以接收 4 个参数：第三个参数指定内部初始状态，
//在这里，仅仅 Active有内部状态，该状态就是需要传入到其基类的内部初始状态。
//第四个参数指定是否有某种历史状态需要保持
// Active 是最外层的状态， 因此需要传输其所属状态机
struct Active : sc::simple_state<Active, StopWatch, Stopped >
{
public:
    typedef sc::transition<EvReset, Active> reactions;

    Active():elapsedTime(0.0){}
    double ElapsedTime() const { return elapsedTime; }
    double &ElapsedTime() { return elapsedTime; }
private:
    double elapsedTime;
};

// Stopped 和Running 都指定 Active 为其上下文,这将使这两个状态内嵌于 Active中
struct Running : IElapsedTime,  sc::simple_state< Running, Active > 
{
public:
    typedef sc::transition<EvStartStop, Stopped> reactions;

    Running():startTime(std::time(0)){}
    ~Running()
    {
        context<Active>().ElapsedTime() = ElapsedTime();
    }

    virtual double ElapsedTime() const 
    {
        return context< Active >().ElapsedTime() + std::difftime(std::time(0), startTime);
    }
private:
    std::time_t startTime;
};
struct Stopped : IElapsedTime, sc::simple_state< Stopped, Active >
{
    typedef sc::transition<EvStartStop, Running> reactions;

    virtual double ElapsedTime() const 
    {
        return context< Active >().ElapsedTime();
    }
};

//由于状态上下文必须一个完整的类型（例如，不允许前置声明）， 
//状态机需要由外而内定义。我们总是从最外层开始定义，我们也可以宽度优先或深度优先方式定义

int main()
{
     StopWatch myWatch;
     myWatch.initiate();
     sleep(4);
     std::cout << myWatch.ElapsedTime() << std::endl;
     myWatch.process_event(EvStartStop());
     sleep(5);
     std::cout << myWatch.ElapsedTime() << std::endl;
     myWatch.process_event(EvStartStop());
     sleep(3);
     std::cout << myWatch.ElapsedTime() << std::endl;
     myWatch.process_event(EvStartStop());
     sleep(3);
     std::cout << myWatch.ElapsedTime() << std::endl;
     myWatch.process_event(EvReset());
     std::cout << myWatch.ElapsedTime() << std::endl;
     return 0;
}
