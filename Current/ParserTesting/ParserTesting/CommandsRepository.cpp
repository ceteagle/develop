#include <iostream>

#include "CommandsRepository.h"
#include "Collection.h"
#include "CommandsContainer.h"

#include "GenericCommand.h"

template<typename T>
void AddProcessedCommandsToVector(std::vector<std::string>& processedCommandNames, std::vector<const ICommand*>& allCommandsVector, const std::vector<T>& commandsVector)
{
    if (commandsVector.empty())
        return;

    for (typename std::vector<T>::const_iterator commandIt = commandsVector.begin(); commandIt != commandsVector.end(); ++commandIt)
    {
        allCommandsVector[commandIt->m_index] = &*commandIt;
    }

    processedCommandNames.push_back(commandsVector.begin()->Name());
}

bool IsProcessedGenericCommand(const std::string& commandName)
{
    return	(_stricmp(commandName.c_str(), "CROD") == 0) ||
        (_stricmp(commandName.c_str(), "PROD") == 0) ||
        (_stricmp(commandName.c_str(), "PBEAM") == 0) ||
        (_stricmp(commandName.c_str(), "RBE3") == 0);
}

void CommandsRepository::AddGenericCommandsToMap()
{
    const std::vector<GenericCommand>& commandsVector = (*m_pContainer).m_commandContainer.m_commands;
    if (commandsVector.empty())
        return;

    for (std::vector<GenericCommand>::const_iterator commandIt = commandsVector.begin(); commandIt != commandsVector.end(); ++commandIt)
    {
        m_NameCommandMap[commandIt->m_name].push_back(&*commandIt);
    }

    for (std::map<std::string, std::vector<const ICommand*> >::const_iterator mapIt = m_NameCommandMap.begin(); mapIt != m_NameCommandMap.end(); ++mapIt)
    {
        if (IsProcessedGenericCommand(mapIt->first))
            m_ProcessedCommands.push_back(mapIt->first);
        else
            m_UnProcessedCommands.push_back(mapIt->first);
    }
}

void CommandsRepository::AddGenericCommandsToVector()
{
    const std::vector<GenericCommand>& commandsVector = Commands();
    if (commandsVector.empty())
        return;

    for (std::vector<GenericCommand>::const_iterator commandIt = commandsVector.begin(); commandIt != commandsVector.end(); ++commandIt)
    {
        m_Commands[commandIt->m_index] = &*commandIt;
    }
}

bool CommandsRepository::CommandMapsInitialized()
{
    return !m_ProcessedCommands.empty() || !m_UnProcessedCommands.empty();
}

std::vector<GenericCommand>&        CommandsRepository::Commands()              const { return (*m_pContainer).m_commandContainer.m_commands; }
std::vector<PCOMPCommand>&			CommandsRepository::PCOMPCommands()			const { return (*m_pContainer).m_pcompCommandContainer.m_commands; }
//std::vector<PCOMPGCommand>&			CommandsRepository::PCOMPGCommands()		const { return (*m_pContainer).m_pcompgCommandContainer.m_commands; }
//std::vector<PCOMPSCommand>&			CommandsRepository::PCOMPSCommands()		const { return (*m_pContainer).m_pcompsCommandContainer.m_commands; }


CommandsRepository::CommandsRepository()
{
    m_pContainer = new CommandsContainer();
}

CommandsRepository::~CommandsRepository()
{
    delete m_pContainer;
    m_pContainer = NULL;
}

void CommandsRepository::Clear()
{
    (*m_pContainer).clear();
}

void CommandsRepository::Destroy()
{
    delete this;
}

void CommandsRepository::FreeMemory(void* pMemory)
{
    delete[] pMemory;
}

int CommandsRepository::Serialize(char** pStream, size_t* pLength) const
{
    return 0;
}

int CommandsRepository::Deserialize(const char* pStream, size_t length)
{
    return 0;
}

ICollection<ICommand*>* CommandsRepository::GetCommandsByName(const char* name)
{
    std::string commandName = Command::ConvertToCommandName(name);

    //if (commandName == Command::ConvertToCommandName("PCOMP"))
    //    return new Collection<std::vector<PCOMPCommand>::iterator, ICommand*>(PCOMPCommands().begin(), PCOMPCommands().end());
    //if (commandName == Command::ConvertToCommandName("PCOMPG"))
    //    return new Collection<std::vector<PCOMPGCommand>::iterator, ICommand*>(PCOMPGCommands().begin(), PCOMPGCommands().end());
    //if (commandName == Command::ConvertToCommandName("PCOMPS"))
    //    return new Collection<std::vector<PCOMPSCommand>::iterator, ICommand*>(PCOMPSCommands().begin(), PCOMPSCommands().end());

    if (!CommandMapsInitialized())
        FillCommandMaps();

    std::vector<const ICommand*>& commands = m_NameCommandMap[commandName];
    return new PtrCollection<std::vector<const ICommand*>::iterator, ICommand*>(commands.begin(), commands.end());
}

int CommandsRepository::GetCommandNamesCount(eFECommandsType eCommandsType)
{
    size_t count = 0;
    if ((eCommandsType & eFECommandsUnProcessed) == eFECommandsUnProcessed)
        count += m_UnProcessedCommands.size();
    if ((eCommandsType & eFECommandsProcessed) == eFECommandsProcessed)
        count += m_ProcessedCommands.size();

    return static_cast<int>(count);
}

const char* CommandsRepository::GetCommandName(eFECommandsType eCommandsType, int index)
{
    if (eCommandsType == eFECommandsAll)
    {
        if (index < m_UnProcessedCommands.size())                // Command is unprocessed command
        {
            eCommandsType = eFECommandsUnProcessed;
        }
        else                                                    // Command is processed command
        {
            eCommandsType = eFECommandsProcessed;
            index -= static_cast<int>(m_UnProcessedCommands.size());
        }
    }

    if (eCommandsType == eFECommandsUnProcessed)
    {
        if (index < 0 || index >= m_UnProcessedCommands.size())
            return NULL;

        return m_UnProcessedCommands[index].c_str();
    }

    if (eCommandsType == eFECommandsProcessed)
    {
        if (index < 0 || index >= m_ProcessedCommands.size())
            return NULL;

        return m_ProcessedCommands[index].c_str();
    }

    return NULL;
}

const ICommand* CommandsRepository::GetCommandByIndex(int index)
{
    if (index < 0 || index >= m_Commands.size())
        return NULL;

    return m_Commands[index];
}

const char* CommandsRepository::GetFormat()
{
    return "Nastran";
}

int CommandsRepository::GetCommandsCount() const
{
    return (int)m_Commands.size();
}

size_t CommandsRepository::AllCommandsSize() const
{
    size_t size = 0;
    /*size = Commands().size();
    size += PCOMPCommands().size();
    size += PCOMPGCommands().size();
    size += PCOMPSCommands().size();*/

    return size;
}

void CommandsRepository::FillCommandMaps()
{
    m_NameCommandMap.clear();
    AddGenericCommandsToMap();

    m_Commands.clear();
    m_Commands.resize(AllCommandsSize(), NULL);

    AddGenericCommandsToVector();
    /*AddProcessedCommandsToVector(m_ProcessedCommands, m_Commands, PCOMPCommands());
    AddProcessedCommandsToVector(m_ProcessedCommands, m_Commands, PCOMPGCommands());
    AddProcessedCommandsToVector(m_ProcessedCommands, m_Commands, PCOMPSCommands());*/
}
