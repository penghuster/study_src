#pragma once

#include "command.h"

namespace RCTRL
{
//    class Command;

    class SimpleRemoteControl
    {
    private:
        Command *m_cmd;

    public:
        SimpleRemoteControl();
        ~SimpleRemoteControl();

        void pressButton(int slot);
        void setCommand(Command* cmd);

    };
}
