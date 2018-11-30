#pragma once
#include <string>
#include <map>

#include "Parser.h"
#include "CommandsContainer.h"
#include "CommandPtr.h"
#include "CommandGrammar.h"

struct CommandContinueInfo
{
    CommandContinueInfo() : m_NextFieldIndex(0)
    {

    }

    CommandPtr          m_pCommand;
    int                 m_NextFieldIndex;
};

struct DatabaseHelper {

    DatabaseHelper(Parser* pParser) :
        m_pParser(pParser),
        m_LastNasCommandIndex(-1)
    {
    }

    ~DatabaseHelper()
    {
        m_continueCommandMap.clear();
    }

    int nextCommandIndex() { return ++m_LastNasCommandIndex; }

    int m_LastNasCommandIndex;
    
    std::map<std::string, CommandContinueInfo > m_continueCommandMap;

    Parser* m_pParser;
};



