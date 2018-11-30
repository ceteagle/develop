#pragma once

#include <string>

#include "CommandContainer.h"
#include "CommandPtr.h"
#include "CommandGrammar.h"
#include "FieldVisitor.h"

#include "GenericCommand.h"
#include "PCOMPCommand.h"

struct CommandsContainer {
    CommandContainer<GenericCommand>		m_commandContainer;
    CommandContainer<PCOMPCommand>			m_pcompCommandContainer;
    //CommandContainer<PCOMPGCommand>			m_pcompgCommandContainer;
    //CommandContainer<PCOMPSCommand>			m_pcompsCommandContainer;

    template<typename T>
    void clear(T& container)
    {
        T emptyContainer;
        container.swap(emptyContainer);
    }

    void clear()
    {
        clear(m_commandContainer.m_commands);

        clear(m_pcompCommandContainer.m_commands);
        //clear(m_pcompgCommandContainer.m_commands);
        //clear(m_pcompsCommandContainer.m_commands);
    }

    CommandPtr AddCommandAndVisit(std::string name, int index, int offset, CommandGrammar::CommandAttrType const& attr)
    {
        CommandPtr ptrCmd = AddCommand(name, index);

        Visit(ptrCmd, offset, attr);

        return ptrCmd;
    }

    CommandPtr AddCommand(std::string name, int index)
    {
        boost::to_upper(name);
        CommandPtr retVal;
        if (name == "PCOMP")
        {
            m_pcompCommandContainer.m_commands.push_back(PCOMPCommand(name, index));
            retVal.m_pContainer = &m_pcompCommandContainer;
        }
        //else if (name == "PCOMPG")
        //{
        //    m_pcompgCommandContainer.m_commands.push_back(PCOMPGCommand(name, index));
        //    retVal.m_pContainer = &m_pcompgCommandContainer;
        //}
        //else if (name == "PCOMPS")
        //{
        //    m_pcompsCommandContainer.m_commands.push_back(PCOMPSCommand(name, index));
        //    retVal.m_pContainer = &m_pcompsCommandContainer;
        //}
        else
        {
            m_commandContainer.m_commands.push_back(GenericCommand(name, index));
            retVal.m_pContainer = &m_commandContainer;
        }

        if (retVal.m_pContainer)
            retVal.m_Index = retVal.m_pContainer->Count() - 1;

        return retVal;
    }

    void Visit(Command * ptrCmd, int offset, CommandGrammar::CommandAttrType const& attr) const
    {
        static VisitableFieldData fieldData;
        static FieldVisitor fieldVisitor(&fieldData);

        if (ptrCmd != NULL)
        {
            // Set command arguments
            for (std::vector< boost::variant<int, double, std::vector<char> > >::const_iterator it = boost::fusion::at_c<1>(attr).begin(); it != boost::fusion::at_c<1>(attr).end(); ++it)
            {
                fieldData.Reset();
                if (ptrCmd->VisitField(std::distance(boost::fusion::at_c<1>(attr).begin(), it) + offset, fieldData))
                    boost::apply_visitor(fieldVisitor, *it);
            }
        }
    }
};
