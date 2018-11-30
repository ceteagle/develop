#pragma once

#include "../../Interfaces/IFEParser.h"
#include <string>

namespace Ans { namespace FEParser { namespace Impl 
{
    class FEParserSettings : public Ans::FEParser::Interfaces::IFEParserSettings
    {
    public:
        virtual void SetFilePath(const char *filePath) override
        {
            m_filePath = filePath;
        }

        virtual const char* GetFilePath() const override
        {
            return m_filePath.c_str();
        }

        virtual void Destroy() override
        {
            delete this;
        }

    private:
        std::string m_filePath;
    };

}}}