#pragma once

#include "Interfaces.h"

struct CommandsRepository;

namespace Nastran {
    struct CommandsRepository;
}

struct DatabaseHelper;

struct Parser : public IFEParser
{
public:
    int Parse(const char* inStream, size_t inSize, ICommandRepository* piCommandRepo, const IFEParserSettings *piParserSettings) override;
    void Destroy() override;

    int ParseInclude(const char* includeFile) const;

private:
    int Parse(const char* begin, const char* end) const;
    void UpdateCommands();

private:
    CommandsRepository* m_pCommandRepo;
    const IFEParserSettings* m_piParserSettings;
    DatabaseHelper*   m_pDatabaseHelper;
};
