#pragma once
#include <vector>

#include "Command.h"

template<typename T>
struct CommandContainer : ICommandContainer
{
    std::vector<T>			            m_commands;

    int Count() override { return m_commands.size(); }
    Command* Item(int index) override { return (index < 0 || index >= m_commands.size()) ? NULL : &m_commands[index]; }

    //MSGPACK_DEFINE(m_commands)
};


