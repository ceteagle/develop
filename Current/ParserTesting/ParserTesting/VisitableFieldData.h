#pragma once

#include <string>

struct VisitableFieldData {
    VisitableFieldData() {
        Reset();
    }

    short *					m_TypePtr;

    int *					m_IntPtr;
    unsigned int *			m_UintPtr;
    long *					m_LongPtr;
    double *				m_DoublePtr;
    float *					m_FloatPtr;
    std::string *			m_StringPtr;
    char**	                m_CharArrayPtr;

    void Reset()
    {
        m_TypePtr = NULL;
        m_IntPtr = NULL;
        m_UintPtr = NULL;
        m_LongPtr = NULL;
        m_DoublePtr = NULL;
        m_FloatPtr = NULL;
        m_StringPtr = NULL;
        m_CharArrayPtr = NULL;
    }
};

