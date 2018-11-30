#pragma once

#include <boost/algorithm/string/case_conv.hpp>

#include "Interfaces.h"
#include "GenericCommand.h"

struct PCOMPData : virtual IPCOMPData {
    PCOMPData()
    {
        m_MID = 0;
        m_T = m_THETA = DBL_MAX;
        m_SOUT = "";
    }

    // IPCOMPData
    unsigned int		MID() const override { return m_MID; };
    double				T() const override { return m_T; };
    double				THETA() const override { return m_THETA; };
    std::string			SOUT() const override { return m_SOUT; };

    bool ProcessLayer(const IPCOMPData * previous) {
        if (m_MID == 0 && m_T == DBL_MAX && m_THETA == DBL_MAX && m_SOUT == "")
            return false;

        if (previous == NULL)
            return true;

        if (m_MID == 0)
            m_MID = previous->MID();
        if (m_T == DBL_MAX)
            m_T = previous->T();

        if (m_THETA == DBL_MAX)
            m_THETA = 0.0;
        if (m_SOUT == "")
            m_SOUT = "NO";

        return true;
    };

    unsigned int m_MID;
    double m_T;
    double m_THETA;
    std::string m_SOUT;
};

struct PCOMPCommand : GenericCommand, virtual IPCOMPCommand {
    PCOMPCommand(const std::string& name = "", int index = 0) : GenericCommand(name, index)
    {
        m_PID = 0;
        m_Z0 = DBL_MAX;
        m_NSM = 0.0;
        m_SB = 0.0;
        m_FT = "";
        m_TREF = 0.0;
        m_GE = 0.0;
        m_LAM = "";
    }

    void PostProcess()
    {
        std::vector<PCOMPData> newData;
        PCOMPData * previous = NULL;
        int layerCount = m_data.size();
        for (int layer = 0; layer < layerCount; layer++)
        {
            if (m_data[layer].ProcessLayer(previous) == false)
            {
                continue;
            }
            newData.push_back(m_data[layer]);
            previous = &(m_data[layer]);
        }
        m_data.clear();
        m_data = newData;

        std::string lam = m_LAM;
        boost::to_upper(lam);
        if (lam == "SYM")
        {
            int layerCount = m_data.size();
            for (int layer = layerCount - 1; layer >= 0; layer--)
            {
                PCOMPData data = m_data[layer];
                m_data.push_back(data);
            }
        }

        if (m_Z0 == DBL_MAX)
        {
            int layerCount = m_data.size();
            double totalThickness = 0.0;
            for (int layer = 0; layer < layerCount; layer++)
            {
                totalThickness += m_data[layer].m_T;
            }

            m_Z0 = -0.5 * totalThickness;
        }
    }

    VisitableFieldData* VisitField(int index, VisitableFieldData& fieldData) override
    {
        switch (index)
        {
        case 0:
            fieldData.m_UintPtr = &m_PID;
            break;
        case 1:
            fieldData.m_DoublePtr = &m_Z0;
            break;
        case 2:
            fieldData.m_DoublePtr = &m_NSM;
            break;
        case 3:
            fieldData.m_DoublePtr = &m_SB;
            break;
        case 4:
            fieldData.m_StringPtr = &m_FT;
            break;
        case 5:
            fieldData.m_DoublePtr = &m_TREF;
            break;
        case 6:
            fieldData.m_DoublePtr = &m_GE;
            break;
        case 7:
            fieldData.m_StringPtr = &m_LAM;
            break;
        default:
        {
            int modIndex = index % 8;
            switch (modIndex)
            {
            case 0:
            case 4:
            {
                PCOMPData data;
                m_data.push_back(data);
                m_currentDataIndex = m_data.size() - 1;
                fieldData.m_UintPtr = &m_data[m_currentDataIndex].m_MID;
            }
            break;
            case 1:
            case 5:
                fieldData.m_DoublePtr = &m_data[m_currentDataIndex].m_T;
                break;
            case 2:
            case 6:
                fieldData.m_DoublePtr = &m_data[m_currentDataIndex].m_THETA;
                break;
            case 3:
            case 7:
                fieldData.m_StringPtr = &m_data[m_currentDataIndex].m_SOUT;
                break;
            default:
                return NULL;
            }
        }
        return &fieldData;
        }
        return &fieldData;
    }

    void FillArguments() override
    {
        if (!m_arguments.empty())
            return;

        m_arguments.emplace_back(m_PID);
        m_arguments.emplace_back(m_Z0);
        m_arguments.emplace_back(m_NSM);
        m_arguments.emplace_back(m_SB);
        m_arguments.emplace_back(m_FT.c_str());
        m_arguments.emplace_back(m_TREF);
        m_arguments.emplace_back(m_GE);
        m_arguments.emplace_back(m_LAM.c_str());

        for (std::vector<PCOMPData>::const_iterator dataIt = m_data.begin(); dataIt != m_data.end(); ++dataIt)
        {
            m_arguments.emplace_back(dataIt->m_MID);
            m_arguments.emplace_back(dataIt->m_T);
            m_arguments.emplace_back(dataIt->m_THETA);
            m_arguments.emplace_back(dataIt->m_SOUT.c_str());
        }
    }

    // IPCOMPCommand
    unsigned int		PID() const override { return m_PID; };
    double				Z0() const override { return m_Z0; };
    double				NSM() const override { return m_NSM; };
    double				SB() const override { return m_SB; };
    std::string			FT() const override { return m_FT; };
    double				TREF() const override { return m_TREF; };
    double				GE() const override { return m_GE; };
    std::string			LAM() const override { return m_LAM; };


    unsigned int Count() const override { return m_data.size(); }
    const IPCOMPData* Item(unsigned int index) const override
    {
        if (index < 0 || index >= m_data.size())
        {
            return NULL;
        }
        return &m_data[index];
    }

    std::vector<PCOMPData> m_data;
    unsigned int m_currentDataIndex;

    unsigned int		m_PID;
    double				m_Z0;
    double				m_NSM;
    double				m_SB;
    std::string			m_FT;
    double				m_TREF;
    double				m_GE;
    std::string			m_LAM;
};
