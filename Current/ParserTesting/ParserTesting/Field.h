#pragma once

#include <string>

#include "Constants.h"

union FieldData
{
    int						m_IntVal;
    double					m_DoubleVal;
    char*					m_StringVal;
};

struct Field
{
    Field() : m_Type(FieldDataTypeUndefined)
    {
        m_Data.m_StringVal = NULL;
    }

    Field(unsigned int uintVal) : m_Type(FieldDataTypeUndefined)
    {
        operator=(static_cast<int>(uintVal));
    }

    Field(int intVal) : m_Type(FieldDataTypeUndefined)
    {
        operator=(intVal);
    }

    Field(double dblVal) : m_Type(FieldDataTypeUndefined)
    {
        operator=(dblVal);
    }

    Field(const char* strVal) : m_Type(FieldDataTypeUndefined)
    {
        operator=(strVal);
    }

    Field(const Field& field) : m_Type(FieldDataTypeUndefined)
    {
        operator=(field);
    }

    Field& operator=(const Field& field)
    {
        switch (field.m_Type)
        {
        case FieldDataTypeInt:
            return operator=(field.m_Data.m_IntVal);
        case FieldDataTypeDouble:
            return operator=(field.m_Data.m_DoubleVal);
        case FieldDataTypeString:
            return operator=(field.m_Data.m_StringVal);
        }

        Clear();
        m_Type = field.m_Type;
        m_Data = field.m_Data;
        return *this;
    }

    Field& operator=(int intVal)
    {
        Clear();

        m_Type = FieldDataTypeInt;
        m_Data.m_IntVal = intVal;
        return *this;
    }

    Field& operator=(double dblVal)
    {
        Clear();

        m_Type = FieldDataTypeDouble;
        m_Data.m_DoubleVal = dblVal;
        return *this;
    }

    Field& operator=(const char* strVal)
    {
        Clear();

        m_Type = FieldDataTypeString;
        if (strVal)
        {
            size_t len = strVal ? strlen(strVal) : 0;
            m_Data.m_StringVal = new char[len + 1];
            memcpy(m_Data.m_StringVal, strVal, len * sizeof(char));
            m_Data.m_StringVal[len] = '\0';
        }
        return *this;
    }

    bool operator<(const Field& rhs) const
    {
        if (m_Type == rhs.m_Type)
        {
            switch (m_Type)
            {
            case FieldDataTypeInt:
                return m_Data.m_IntVal < rhs.m_Data.m_IntVal;
            case FieldDataTypeDouble:
                return m_Data.m_DoubleVal < rhs.m_Data.m_DoubleVal;
            case FieldDataTypeString:
                return strcmp(m_Data.m_StringVal, rhs.m_Data.m_StringVal) < 0;
            default:
                return false;
            }
        }

        return m_Type < rhs.m_Type;
    }

    bool operator>(const Field& rhs) const
    {
        if (m_Type == rhs.m_Type)
        {
            switch (m_Type)
            {
            case FieldDataTypeInt:
                return m_Data.m_IntVal > rhs.m_Data.m_IntVal;
            case FieldDataTypeDouble:
                return m_Data.m_DoubleVal > rhs.m_Data.m_DoubleVal;
            case FieldDataTypeString:
                return strcmp(m_Data.m_StringVal, rhs.m_Data.m_StringVal) > 0;
            default:
                return false;
            }
        }

        return m_Type < rhs.m_Type;
    }

    bool operator==(const Field& rhs) const
    {
        if (m_Type == rhs.m_Type)
        {
            switch (m_Type)
            {
            case FieldDataTypeInt:
                return m_Data.m_IntVal == rhs.m_Data.m_IntVal;
            case FieldDataTypeDouble:
                return m_Data.m_DoubleVal == rhs.m_Data.m_DoubleVal;
            case FieldDataTypeString:
                return strcmp(m_Data.m_StringVal, rhs.m_Data.m_StringVal) == 0;
            default:
                return false;
            }
        }

        return m_Type == rhs.m_Type;
    }

    bool IsUndefined() const { return m_Type == FieldDataTypeUndefined; }
    bool IsInt()       const { return m_Type == FieldDataTypeInt; }
    bool IsDouble()    const { return m_Type == FieldDataTypeDouble; }
    bool IsString()    const { return m_Type == FieldDataTypeString; }
    bool IsNumeric()   const { return IsInt() || IsDouble(); }

    int			IntVal()    const { return IsInt() ? m_Data.m_IntVal : IsDouble() ? static_cast<int>(m_Data.m_DoubleVal) : 0; }
    double		DoubleVal() const { return IsInt() ? static_cast<double>(m_Data.m_IntVal) : IsDouble() ? m_Data.m_DoubleVal : 0; }
    const char* StringVal() const { return IsString() ? m_Data.m_StringVal : static_cast<const char*>(0); }

    ~Field()
    {
        Clear();
    }

    void Clear()
    {
        if (m_Type == FieldDataTypeString)
        {
            delete[] m_Data.m_StringVal;
            m_Data.m_StringVal = NULL;
        }
    }

    short int				m_Type;
    FieldData				m_Data;
};

