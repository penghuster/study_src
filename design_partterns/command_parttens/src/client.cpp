#include <iostream>
#include "light.h"
#include "light_on_command.h"
#include "simple_rctrl.h"

using namespace std;
using namespace RCTRL;
int main(int argc, char** argv)
{
    SimpleRemoteControl* control = new SimpleRemoteControl();
    Light *light = new Light();
    LightOnCommand * cmd = new LightOnCommand(light);
    control->setCommand(cmd);
    control->pressButton(1);
    cout << "hello world." << endl;
}
