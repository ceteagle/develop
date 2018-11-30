#include <string>

#include "Parser.h"
#include "CommandsContainer.h"
#include "CommandsRepository.h"
#include "COMMAND_Actor.hpp"
#include "CONTINUE_Actor.hpp"
#include "SKIP_Actor.hpp"

#include "Grammar.hpp"

std::string RemoveChar(const char* input, const char c)
{
    std::string output;
    //output.reserve(strlen(input));
    //while (*input != '\0')
    //{
    //    if (*input != c)
    //        output.push_back(*input);

    //    input += 1;
    //}
    return output;
}

//std::string ResolveFilePath(const IFEParserSettings &feParserSettings, const char* filePath)
//{
    //ans_string filePathWithoutQuotes = (StringUtilities().a2t(RemoveChar(filePath, '\"').c_str()));

    //// check if the file exists in the current directory
    //if (PathUtilities::FileExists(filePathWithoutQuotes))
    //    return filePathWithoutQuotes;

    //// maybe it is a relative path
    //const char* rootFilePath = feParserSettings.GetFilePath();
    //if (!rootFilePath)
    //    throw std::runtime_error("IFEParserSettings::GetFilePath rturned null");

    //ans_string absoluteFilePath = PathUtilities::Combine(PathUtilities::GetDirectory(StringUtilities().a2t(rootFilePath)), filePathWithoutQuotes);
    //if (PathUtilities::FileExists(absoluteFilePath))
    //    return absoluteFilePath;

    //return ans_string();
    //throw std::runtime_error(std::string("Cannot resolve file: ") + filePath);
//}

int Parser::Parse(const char* inStream, size_t inSize, ICommandRepository* piCommandRepo, const IFEParserSettings *piParserSettings)
{
    CommandsRepository* pRepo = dynamic_cast<CommandsRepository*>(piCommandRepo);
    if (!pRepo)
    {
        return 1;
    }

    m_pCommandRepo = pRepo;
    m_piParserSettings = piParserSettings;
    m_pDatabaseHelper = new DatabaseHelper(this);
    if (Parse(inStream, inStream + inSize) != 0)
        return 1;

    UpdateCommands();

    return 0;
}

void Parser::Destroy()
{
    delete this;
}

int Parser::Parse(const char * begin, const char * end) const
{
    CommandsContainer& container = const_cast<CommandsContainer&>(m_pCommandRepo->GetContainer());

    COMMAND_Actor       command_actor(container, *m_pDatabaseHelper);
    CONTINUE_Actor      continue_actor(container, *m_pDatabaseHelper);
    SKIP_Actor          skip_actor;

    Grammar<
        const char*,
        COMMAND_Actor,
        CONTINUE_Actor,
        SKIP_Actor
    >
        nas_g(
            command_actor,
            continue_actor,
            skip_actor
        );

    return phrase_parse(begin, end, nas_g, boost::spirit::ascii::blank) && begin == end ? 0 : 1;
}

//int Parser::ParseInclude(const char * includeFile) const
//{
//    if (!m_piParserSettings)
//        return 1;
//
//    size_t lSize;
//    char* storage = IOHelper::FileToByteArray((ResolveFilePath(*m_piParserSettings, includeFile).c_str()), lSize);
//    if (!storage)
//    {
//        return 1;
//    }
//
//    int retVal = Parse(storage, storage + lSize);
//
//    delete[] storage;
//    return retVal;
//}

void Parser::UpdateCommands()
{
    //NASCommandsContainer& nasContainer = const_cast<NASCommandsContainer&>(m_pCommandRepo->GetContainer());

    //ICollection<ICommand*> * commands = m_pCommandRepo->GetCommandsByName("PCOMP");
    //for (int iCommand = 0; iCommand < commands->Count(); ++iCommand)
    //{
    //    auto pcomp = dynamic_cast<PCOMPCommand*>(commands->Item(iCommand));
    //    if (pcomp == nullptr)
    //        continue;
    //    pcomp->PostProcess();
    //}

    //commands = m_pCommandRepo->GetCommandsByName("PCOMPG");
    //for (int iCommand = 0; iCommand < commands->Count(); ++iCommand)
    //{
    //    auto pcomp = dynamic_cast<PCOMPGCommand*>(commands->Item(iCommand));
    //    if (pcomp == nullptr)
    //        continue;
    //    pcomp->PostProcess();
    //}

    //commands = m_pCommandRepo->GetCommandsByName("PCOMPS");
    //for (int iCommand = 0; iCommand < commands->Count(); ++iCommand)
    //{
    //    auto pcomp = dynamic_cast<PCOMPSCommand*>(commands->Item(iCommand));
    //    if (pcomp == nullptr)
    //        continue;
    //    pcomp->PostProcess();
    //}
}