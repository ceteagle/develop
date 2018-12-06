#pragma once

#include <boost/variant/static_visitor.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <vector>

#include "Constants.h"
#include "VisitableFieldData.h"

class FieldVisitor : public boost::static_visitor<>
{
    VisitableFieldData * m_field;

public:
    FieldVisitor(VisitableFieldData * field) : m_field(field)
    {
    }

    void operator()(int i) const
    {
        if (m_field == NULL)
            return;

        if (m_field->m_TypePtr != NULL)
            *m_field->m_TypePtr = FieldDataTypeInt;

        if (m_field->m_IntPtr != NULL)
            *(m_field->m_IntPtr) = i;
        else if (m_field->m_UintPtr != NULL)
            *(m_field->m_UintPtr) = i;
        else if (m_field->m_LongPtr != NULL)
            *(m_field->m_LongPtr) = i;
    }

    void operator()(double i) const
    {
        if (m_field == NULL)
            return;

        if (m_field->m_TypePtr != NULL)
            *m_field->m_TypePtr = FieldDataTypeDouble;

        if (m_field->m_DoublePtr != NULL)
            *(m_field->m_DoublePtr) = i;
        else if (m_field->m_FloatPtr != NULL)
            *(m_field->m_FloatPtr) = static_cast<float>(i);
    }

    void operator()(const std::vector<char>& str) const
    {
        if (m_field == NULL)
            return;

        if (m_field->m_TypePtr != NULL)
            *m_field->m_TypePtr = FieldDataTypeString;

        if (m_field->m_StringPtr == NULL && m_field->m_CharArrayPtr == NULL)
            return;

        /*if(str.empty())
        return;*/

        if (m_field->m_StringPtr)
        {
            m_field->m_StringPtr->assign(str.begin(), str.end());
            boost::to_upper(*(m_field->m_StringPtr));
        }
        else if (m_field->m_CharArrayPtr)
        {
            // Assign Data
            *(m_field->m_CharArrayPtr) = new char[str.size() + 1];
            if (!str.empty())
            {
                memcpy(*(m_field->m_CharArrayPtr), &*str.begin(), str.size() * sizeof(char));
            }
            (*(m_field->m_CharArrayPtr))[str.size()] = '\0';

            boost::to_upper(*(m_field->m_CharArrayPtr));
        }
    }
};

