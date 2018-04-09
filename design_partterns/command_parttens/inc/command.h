#pragma once


namespace RCTRL
{
    class Command
    {
    public:
        virtual void execute() = 0;
        virtual ~Command(){}

    };
}
