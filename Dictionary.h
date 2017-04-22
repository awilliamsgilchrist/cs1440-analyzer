#ifndef GENERICDICTIONARY_DICTIONARY_H
#define GENERICDICTIONARY_DICTIONARY_H

#include <vector>
#include "KeyValue.h"

enum Exception{DefaultException};

template <typename K, typename V>
class Dictionary
{
private:
    KeyValue<K, V>* m_dict;
    unsigned int m_size;
    unsigned int m_count;

    void resize();
    void reindex(unsigned int index);
public:
    unsigned int getCount() {return m_count;}
    void add(K key, V value);
    V get(K key);
    V getByIndex(unsigned int index);
    V* getRef(K key);
    V* getRefByIndex(unsigned int index);
    std::vector<KeyValue<K, V>> getAll();
    void remove(K key);
    void remove(unsigned int index);
    void changeVal(K key, V newVal);

    Dictionary(unsigned int size = 10);
    Dictionary(const Dictionary& toBeCopied);
    ~Dictionary();
};

template <typename K, typename V>
void Dictionary<K, V>::resize()
{
    if(m_count == m_size)
    {
        KeyValue<K, V> *oldDict = m_dict;
        m_dict = new KeyValue<K, V>[m_size * 2];

        for (unsigned int i = 0; i < m_count; i++) {
            m_dict[i] = oldDict[i];
        }

        m_size *= 2;
        delete[] oldDict;
        oldDict = nullptr;
    }
}

template <typename K, typename V>
void Dictionary<K, V>::reindex(unsigned int index)
{
    bool reachedHole = false;
    KeyValue<K, V>* oldDict = m_dict;
    m_dict = new KeyValue<K, V>[m_size];

    for(unsigned int i = 0; i < m_count; i++)
    {
        if(i == index)
        {
            reachedHole = true;
            continue;
        }

        if(reachedHole)
        {
            m_dict[i - 1] = oldDict[i];
        }
        else
        {
            m_dict[i] = oldDict[i];
        }
    }

    m_count--;
    delete[] oldDict;
    oldDict = nullptr;
}

template <typename K, typename V>
void Dictionary<K, V>::add(K key, V value)
{
    bool keyIsUnique = true;
    for(unsigned int i = 0; i < m_count; i++)
    {
        if(m_dict[i].getKey() == key)
        {
            keyIsUnique = false;
            break;
        }
    }

    if(keyIsUnique)
    {
        resize();
        m_dict[m_count] = KeyValue<K, V>(key, value);
        m_count++;
    }
    else
    {
        throw DefaultException;
    }
}

template <typename K, typename V>
V Dictionary<K, V>::get(K key)
{
    for(unsigned int i = 0; i < m_count; i++)
    {
        if(m_dict[i].getKey() == key)
        {
            return m_dict[i].getValue();
        }
    }

    throw DefaultException;
}

template <typename K, typename V>
V Dictionary<K, V>::getByIndex(unsigned int index)
{
    if(index < m_count)
    {
        return m_dict[index].getValue();
    }
    else
    {
        throw DefaultException;
    }
}

template <typename K, typename V>
V* Dictionary<K, V>::getRef(K key)
{
    for(unsigned int i = 0; i < m_count; i++)
    {
        if(m_dict[i].getKey() == key)
        {
            return &m_dict[i].getValue();
        }
    }

    throw DefaultException;
}

template <typename K, typename V>
V* Dictionary<K, V>::getRefByIndex(unsigned int index)
{
    if(index < m_count)
    {
        return &m_dict[index].getValue();
    }
    else
    {
        throw DefaultException;
    }
}

template <typename K, typename V>
std::vector<KeyValue<K, V>> Dictionary<K, V>::getAll()
{
    std::vector<KeyValue<K, V>> result;
    for(unsigned int i = 0; i < m_count; i++)
    {
        result.push_back(m_dict[i]);
    }

    return result;
}

template <typename K, typename V>
void Dictionary<K, V>::remove(K key)
{
    for(unsigned int i = 0; i < m_count; i++)
    {
        if(m_dict[i].getKey() == key)
        {
            reindex(i);
            return;
        }
    }

    throw DefaultException;
}

template <typename K, typename V>
void Dictionary<K, V>::remove(unsigned int index)
{
    if(index < m_count)
    {
        reindex(index);
        return;
    }

    throw DefaultException;
}

template <typename K, typename V>
void Dictionary<K, V>::changeVal(K key, V newVal)
{
    for(unsigned int i = 0; i < m_count; i++)
    {
        if(m_dict[i].getKey() == key)
        {
            m_dict[i].setValue(newVal);
            return;
        }
    }

    throw DefaultException;
};

template <typename K, typename V>
Dictionary<K, V>::Dictionary(unsigned int size):
m_size(size),
m_count(0)
{
    m_dict = new KeyValue<K, V>[m_size];
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(const Dictionary& toBeCopied):
m_size(toBeCopied.m_size),
m_count(toBeCopied.m_count)
{
    m_dict = new KeyValue<K, V>[m_size];
    for(unsigned int i = 0; i < m_count; i++)
    {
        m_dict[i] = toBeCopied.m_dict[i];
    }
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
    delete[] m_dict;
    m_dict = nullptr;
}

#endif //GENERICDICTIONARY_DICTIONARY_H
