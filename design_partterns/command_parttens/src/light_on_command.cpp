#include "light_on_command.h"

RCTRL::LightOnCommand::LightOnCommand(Light *val)
{
    light = val;
}

RCTRL::LightOnCommand::~LightOnCommand()
{}

void RCTRL::LightOnCommand::execute()
{
    light->on();
}


