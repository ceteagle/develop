#pragma once

#include <vector>
#include <map>

#include "Interfaces.h"

#include "GenericCommand.h"
#include "PCOMPCommand.h"

struct CommandsContainer;

struct CommandsRepository : public ICommandRepository
{

public:
    CommandsRepository();
    ~CommandsRepository();

    void Clear() override;
    void Destroy() override;
    void FreeMemory(void* pMemory) override;

    int Serialize(char** pStream, size_t* pLength) const override;
    int Deserialize(const char* pStream, size_t length) override;

    ICollection<ICommand*>*	GetCommandsByName(const char* name) override;
    const ICommand*			GetCommandByIndex(int index) override;
    int						GetCommandNamesCount(eFECommandsType eCommandsType) override;
    const char*				GetCommandName(eFECommandsType eCommandsType, int index) override;
    const char*             GetFormat() override;
    int                     GetCommandsCount() const override;

    const CommandsContainer& GetContainer() const { return *m_pContainer; }

private:
    size_t AllCommandsSize() const;
    void FillCommandMaps();
    void AddGenericCommandsToMap();
    void AddGenericCommandsToVector();
    bool CommandMapsInitialized();

    std::vector<GenericCommand>&        Commands() const;
    std::vector<PCOMPCommand>&			PCOMPCommands() const;

    /*std::vector<PCOMPGCommand>&			PCOMPGCommands() const;
    std::vector<PCOMPSCommand>&			PCOMPSCommands() const;*/

private:
    CommandsContainer * m_pContainer;
    std::map<std::string, std::vector<const ICommand*> >	m_NameCommandMap;
    std::vector<const ICommand*>							m_Commands;
    std::vector<std::string>                                m_ProcessedCommands;
    std::vector<std::string>                                m_UnProcessedCommands;
};
