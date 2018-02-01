#include <iostream>
#include "notshooting.hpp"

//在transit< Shooting >() 代码行中需要Shooting的完全定义
//Focusing 是 Shooting的初始化定义，因此我们必须包含 focusing.hpp 
//否则compiler将报出错误， 若shooting没有初始化状态是不需要此头文件

#include "../shooting/shooting.hpp"
#include "../shooting/focusing.hpp"

using namespace std;

NotShooting::NotShooting()
{
    cout << "Enter NotShooting" << endl;
}

NotShooting::~NotShooting()
{
    cout << "Exit NotShooting" << endl;
}

string NotShooting::getStateName() const 
{
    return string("NotShooting");
}

result NotShooting::react(const EvShutterHalf &evShutterHalf)
{
    cout << "NotShooting::react(const EvShutterHalf & evShutterHalf)" << endl;
    if(context< Camera >().isBatteryLow() )
    {
        cout << "Guard: isBatteryLow() is true" << endl;
        //我们不能在此状态响应此事件，所以转向此事件到外部状态
        return forward_event();
    }
    else
    {
        cout << "Guard: isBatteryLow() is true" << endl;
        return transit< Shooting >(); //转变为 Shooting 状态
    }
}
