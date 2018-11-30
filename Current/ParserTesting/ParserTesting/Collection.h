#ifndef COLLECTION_H
#define COLLECTION_H

#include <list>

// Exposed Interfaces
#include "Interfaces.h"

template<typename Iterator, typename EnumeratedType>
struct Enumerator : IEnumerator<EnumeratedType>
{
public:
    Enumerator(Iterator begin, Iterator end) : m_begin(begin), m_end(end) { Enumerator<Iterator, EnumeratedType>::Reset(); }
    virtual ~Enumerator() {};

    EnumeratedType Next() override
    {
        if (m_current != m_end)
        {
            return &*(m_current++);
        }
        else
        {
            return NULL;
        }
    }

    void Skip(int count) override
    {
        const int maxCount = static_cast<int>(std::distance(m_current, m_end));
        m_current += (count < maxCount ? count : maxCount);
    }

    void Reset() override
    {
        m_current = m_begin;
    }

    IEnumerator<EnumeratedType>* Clone() override
    {
        return new Enumerator<Iterator, EnumeratedType>(m_begin, m_end);
    }

    void Destroy() override
    {
        delete this;
    }
    
private:
    Iterator m_current;
    Iterator m_begin;
    Iterator m_end;
};

template<typename Iterator, typename EnumeratedType>
struct Collection : ICollection<EnumeratedType>
{
public:
    Collection(Iterator begin, Iterator end) : m_begin(begin), m_end(end) {}
    virtual ~Collection() {};

    int Count() override
    {
        return static_cast<int>(std::distance(m_begin, m_end));
    }

    EnumeratedType Item(int zeroBasedIndex) override
    {
        if (zeroBasedIndex < 0 || zeroBasedIndex >= Count())
            return NULL;

        return &*(m_begin + zeroBasedIndex);
    }

    Enumerator<Iterator, EnumeratedType>* GetEnumerator() override
    {
        return new Enumerator<Iterator, EnumeratedType>(m_begin, m_end);
    }
    
    void Destroy() override
    {
        delete this;
    }

protected:
    Iterator m_begin;
    Iterator m_end;
};

template<typename Iterator, typename EnumeratedType>
struct PtrEnumerator : IEnumerator<EnumeratedType>
{
public:
    PtrEnumerator(Iterator begin, Iterator end) : m_begin(begin), m_end(end) { PtrEnumerator<Iterator, EnumeratedType>::Reset(); }
    virtual ~PtrEnumerator() {};

    EnumeratedType Next() override
    {
        if (m_current != m_end)
        {
            return const_cast<EnumeratedType>(&**(m_current++));
        }
        else
        {
            return NULL;
        }
    }

    void Skip(int count) override
    {
        const int maxCount = static_cast<int>(std::distance(m_current, m_end));
        m_current += (count < maxCount ? count : maxCount); 
    }

    void Reset() override
    {
        m_current = m_begin;
    }

    IEnumerator<EnumeratedType>* Clone() override
    {
        return new PtrEnumerator<Iterator, EnumeratedType>(m_begin, m_end);
    }

    void Destroy() override
    {
        delete this;
    }

private:
    Iterator m_current;
    Iterator m_begin;
    Iterator m_end;
};

template<typename Iterator, typename EnumeratedType>
struct PtrCollection : ICollection<EnumeratedType>
{
public:
    PtrCollection(Iterator begin, Iterator end) : m_begin(begin), m_end(end) {}
    virtual ~PtrCollection() {};

    int Count() override
    {
        return static_cast<int>(std::distance(m_begin, m_end));
    }

    EnumeratedType Item(int zeroBasedIndex) override
    {
        if (zeroBasedIndex < 0 || zeroBasedIndex >= Count())
            return NULL;

        return const_cast<EnumeratedType>(&**(m_begin + zeroBasedIndex));
    }

    PtrEnumerator<Iterator, EnumeratedType>* GetEnumerator() override
    {
        return new PtrEnumerator<Iterator, EnumeratedType>(m_begin, m_end);
    }
    
    void Destroy() override
    {
        delete this;
    }

protected:
    Iterator m_begin;
    Iterator m_end;
};

template<typename EnumeratedType>
struct MultiEnumerator : IEnumerator<EnumeratedType>
{
public:
    MultiEnumerator(IEnumerator<EnumeratedType>* pEnumerator)
    {
        Add(pEnumerator);   
        MultiEnumerator<EnumeratedType>::Reset();
    }

    virtual ~MultiEnumerator()
    {
        for(typename std::list<IEnumerator<EnumeratedType>* >::iterator enumPtrIt = m_pEnumerators.begin(); enumPtrIt != m_pEnumerators.end(); ++enumPtrIt)
        {
            delete *enumPtrIt;
        }
    }

    void Add(IEnumerator<EnumeratedType>* pEnumerator)
    {
        m_pEnumerators.push_back(pEnumerator);
    }

    EnumeratedType Next() override
    {
        if (m_CurrentEnumPtrIt != m_pEnumerators.end())
        {
            EnumeratedType retVal = (*m_CurrentEnumPtrIt)->Next();
            if(retVal == NULL)
            {
                ++m_CurrentEnumPtrIt;
				return Next();
            }

            return retVal;
        }
        return NULL;
    }

    void Skip(int count) override
    {
        while((count--) > 0 && Next() != NULL){}
    }

    void Reset() override
    {
        m_CurrentEnumPtrIt = m_pEnumerators.begin();
    }

    IEnumerator<EnumeratedType>* Clone() override
    {
        return new MultiEnumerator<EnumeratedType>(m_pEnumerators);
    }

    void Destroy() override
    {
        delete this;
    }
    
private:
    MultiEnumerator(std::list<IEnumerator<EnumeratedType>* >& ranges) : m_pEnumerators(ranges)
    {
        MultiEnumerator<EnumeratedType>::Reset();
    }

private:
    typename std::list<IEnumerator<EnumeratedType>* >::iterator m_CurrentEnumPtrIt;
    std::list<IEnumerator<EnumeratedType>* > m_pEnumerators;
};

template<typename EnumeratedType>
struct MultiCollection : ICollection<EnumeratedType>
{
public:
    MultiCollection(ICollection<EnumeratedType>* pCollection)
    {
        AddCollection(pCollection);
    }
    
    virtual ~MultiCollection()
    {
        for(typename std::list<ICollection<EnumeratedType>*>::iterator collIt = m_pCollections.begin(); collIt != m_pCollections.end(); ++collIt)
        {
            delete *collIt;
        }
    };

    void AddCollection(ICollection<EnumeratedType>* pCollection)
    {
        m_pCollections.push_back(pCollection);
    }

    int Count() override
    {
        int count = 0;
        for(typename std::list<ICollection<EnumeratedType>*>::iterator collPtrIt = m_pCollections.begin(); collPtrIt != m_pCollections.end(); ++collPtrIt)
        {
            count += (*collPtrIt)->Count();
        }

        return count;
    }

    EnumeratedType Item(int index) override
    {
        if (index < 0 || index >= Count())
            return NULL;

        std::pair<ICollection<EnumeratedType>*, int> collPtrAndIdx = CollectionAndIndexByGlobalIndex(index);
        if(collPtrAndIdx.first == NULL)
            return NULL;
        return collPtrAndIdx.first->Item(collPtrAndIdx.second);
    }

    MultiEnumerator<EnumeratedType>* GetEnumerator() override
    {
        typename std::list<ICollection<EnumeratedType>*>::iterator collPtrIt = m_pCollections.begin();
        MultiEnumerator<EnumeratedType>* pEnumerator = new MultiEnumerator<EnumeratedType>((*(collPtrIt++))->GetEnumerator());
        while(collPtrIt != m_pCollections.end())
        {
            pEnumerator->Add((*(collPtrIt++))->GetEnumerator());
        }

        return pEnumerator;
    }
    
    void Destroy() override
    {
        delete this;
    }

private:
    std::pair<ICollection<EnumeratedType>*, int> 
    CollectionAndIndexByGlobalIndex(int globalIndex)
    {
        typename std::list<ICollection<EnumeratedType>*>::iterator collPtrIt = m_pCollections.begin();
		int count = (*collPtrIt)->Count();
		while(count <= globalIndex)
        {
            count += (*(++collPtrIt))->Count();
        }

        while ((*collPtrIt)->Count() == 0)    // Remove all empty collections
        {
            ++collPtrIt;
        }
            
        return std::make_pair(*collPtrIt, globalIndex-count+(*collPtrIt)->Count());
    }

private:
    std::list<ICollection<EnumeratedType>*> m_pCollections;
};

#endif //COMMAND_RANGE_H

