#pragma once

#include <string>
#include <vector>

#include "Interfaces.h"
#include "Command.h"
#include "Field.h"

struct GenericCommand : Command, IGenericCommand {

    GenericCommand(const std::string& name = "", int index = 0) : Command(name, index) {}

    int ArgumentCount() const override
    {
        if (m_arguments.empty())
            const_cast<GenericCommand*>(this)->FillArguments();

        return static_cast<int>(m_arguments.size());
    }

    const Field* Argument(int index) const override
    {
        if (m_arguments.empty())
            const_cast<GenericCommand*>(this)->FillArguments();

        return &m_arguments[index];
    };

    std::vector<Field> 	m_arguments;

    VisitableFieldData* VisitField(int index, VisitableFieldData& fieldData) override
    {
        m_arguments.push_back(Field());
        Field& field = *m_arguments.rbegin();

        fieldData.m_TypePtr = &field.m_Type;
        fieldData.m_IntPtr = &field.m_Data.m_IntVal;
        fieldData.m_DoublePtr = &field.m_Data.m_DoubleVal;
        fieldData.m_CharArrayPtr = &field.m_Data.m_StringVal;

        return &fieldData;
    }

protected:
    virtual void FillArguments() {};
};

