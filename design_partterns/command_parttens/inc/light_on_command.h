#pragma once 

#include "command.h"
#include "light.h"
namespace RCTRL
{
    class LightOnCommand : public Command
    {
    private:
        Light *light;
    public:
        virtual void execute();
        LightOnCommand(Light *val);
        virtual ~LightOnCommand();
    };
}
