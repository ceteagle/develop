#pragma once

#include <string>

#include "Constants.h"
#include "Interfaces.h"
#include "VisitableFieldData.h"

struct Command : virtual ICommand {

    static std::string ConvertToCommandName(const std::string& name)
    {
        std::string commandName = name;
        if (commandName.size() > NAS_COMMAND_LENGTH)		// NASTRAN Comands can be no more than 8 characters, 
            commandName.resize(NAS_COMMAND_LENGTH);			// So don't store additional characters

        return commandName;
    }

    Command(const std::string& name = "", int index = 0) : m_name(ConvertToCommandName(name)), m_index(index)
    {
    }

    const char* Name() const override { return m_name.c_str(); }
    unsigned int Index() const override { return m_index; }

    virtual VisitableFieldData* VisitField(int index, VisitableFieldData& fieldData) = 0;

    std::string 		m_name;
    unsigned int		m_index;

    //MSGPACK_DEFINE(m_name, m_index)
};
