#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
namespace sc = boost::statechart;

// 此处定义为strcut 是为了避免所有成员都要添加 public关键字，如果你不介意，也可以使用class。
//
// 我们需要提前申明初始化状态，因为其必须在定义状态机的地方定义。
 struct Greeting;

// Boost.Statechart 重度使用模板。子类必须总是将该初始化状态作为第一参数传递给基类
// 当状态机进行初始化时，必须被通知进入哪个状态这就是为什么 Greeting 作为第二个参数传递的原因。
struct Machine : sc::state_machine< Machine, Greeting > {};

//对于每个状态都必须指定其所属状态机以及其在状态表中的位置，
//两者是通过simple_state<>的参数来指定。
//因为我们拥有简单的状态机，故其上下文也是状态机。
//相应的，Machine 被当作上下文作为第二参数传递（上下文参数在下文将会进一步说明）。

struct Greeting : sc::simple_state< Greeting, Machine >
{
   // 不论何时状态机进入一个状态，就会创建一个相应的状态类的对象。
   //该对象将保持只要该状态机保持在此状态。最后，在此状态结束时该对象将销毁。
   //因此，进入动作通过定义构造函数来完成，出口动作通过定义析构函数来实现。
    Greeting() { std::cout << "Hello World!\n"; } // entry
    ~Greeting() { std::cout << "Bye Bye World!\n"; } // exit
};

int main()
{
     Machine myMachine;
    // myMachine 在构造函数调用后并没有运行，我们需要通过调用 initiate() 运行该状态机，
    //这将触发 初始状态 Greeting 的构造
    myMachine.initiate();
   // 当离开 main()时，myMachine 的析构将导致当前激活状态被析构
   printf("\n\n\n");
    char buf[256] = {0};
    sprintf(buf, "%c%s", '\003', "gogogog\n");
    printf("buf = %d, %d\n", strlen(buf), strlen("gogogog"));
    printf("%s", buf ); 
    return 0;
}

