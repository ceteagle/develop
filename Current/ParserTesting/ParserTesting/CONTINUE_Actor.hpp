#pragma once

#include <boost/spirit/include/qi.hpp>

#include "CommandPtr.h"
#include "CommandsContainer.h"
#include "DatabaseHelper.hpp"

struct CONTINUE_Actor
{
    CONTINUE_Actor(CommandsContainer& container, DatabaseHelper& databaseHelper) :
        m_Container(container),
        m_DatabaseHelper(databaseHelper)
    {}

    void operator()(CommandGrammar::ContinueAttrType const& attr, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) const
    {
        std::string contStr = std::string(boost::fusion::at_c<0>(attr).begin(), boost::fusion::at_c<0>(attr).end());
        std::map<std::string, CommandContinueInfo>::iterator iter = m_DatabaseHelper.m_continueCommandMap.find(contStr);
        if (iter == m_DatabaseHelper.m_continueCommandMap.end())
            return;

        CommandPtr& ptrCmd = iter->second.m_pCommand;
        m_Container.Visit(ptrCmd, iter->second.m_NextFieldIndex, attr);
        iter->second.m_NextFieldIndex += static_cast<int>(boost::fusion::at_c<1>(attr).size());

        contStr = "";
        if (boost::fusion::at_c<2>(attr))
            contStr.assign(boost::fusion::at_c<2>(attr)->begin(), boost::fusion::at_c<2>(attr)->end());

        if (contStr != iter->first)
        {
            m_DatabaseHelper.m_continueCommandMap[contStr] = iter->second;
            m_DatabaseHelper.m_continueCommandMap.erase(iter);
        }
    }

    CommandsContainer&	m_Container;
    DatabaseHelper&  m_DatabaseHelper;
};
