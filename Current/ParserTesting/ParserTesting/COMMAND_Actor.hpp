#pragma once

#include <boost/spirit/include/qi.hpp>

#include "CommandGrammar.h"
#include "DatabaseHelper.hpp"



struct CommandsContainer;

struct COMMAND_Actor
{
    COMMAND_Actor(CommandsContainer& container, DatabaseHelper& databaseHelper) :
        m_Container(container),
        m_DatabaseHelper(databaseHelper)
    {}

    void operator()(CommandGrammar::CommandAttrType const& attr, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) const
    {
        CommandContinueInfo continueInfo;
        continueInfo.m_pCommand = m_Container.AddCommandAndVisit(std::string(boost::fusion::at_c<0>(attr).begin(), boost::fusion::at_c<0>(attr).end()), m_DatabaseHelper.nextCommandIndex(), 0, attr);
        continueInfo.m_NextFieldIndex = boost::fusion::at_c<1>(attr).size();

        std::string contStr("");
        if (boost::fusion::at_c<2>(attr))
            contStr.assign(boost::fusion::at_c<2>(attr)->begin(), boost::fusion::at_c<2>(attr)->end());

        m_DatabaseHelper.m_continueCommandMap[contStr] = continueInfo;
    }

    CommandsContainer&   m_Container;
    DatabaseHelper&  m_DatabaseHelper;
};
