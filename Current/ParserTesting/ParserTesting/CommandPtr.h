#pragma once

#include "Interfaces.h"

struct CommandPtr
{
    ICommandContainer*	m_pContainer;
    int					m_Index;

    CommandPtr(ICommandContainer* pContainer = NULL, int index = -1) : m_pContainer(pContainer), m_Index(index)
    {
    }

    operator Command*() const
    {
        return operator->();
    }

    Command& operator*() const
    {
        return *(operator->());
    }

    Command* operator->() const
    {
        if (m_Index < 0 || m_Index >= m_pContainer->Count())
            return NULL;

        return m_pContainer->Item(m_Index);
    }
};
