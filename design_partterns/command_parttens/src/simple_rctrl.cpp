#include <cstddef>
#include "command.h"
#include "simple_rctrl.h"

using namespace  std;

RCTRL::SimpleRemoteControl::SimpleRemoteControl():
    m_cmd(nullptr)
{}

RCTRL::SimpleRemoteControl::~SimpleRemoteControl()
{}

void RCTRL::SimpleRemoteControl::setCommand(Command* cmd)
{
    m_cmd = cmd;
}

void RCTRL::SimpleRemoteControl::pressButton(int slot)
{
    m_cmd->execute();
}
