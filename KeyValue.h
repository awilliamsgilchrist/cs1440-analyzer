#ifndef GENERICDICTIONARY_KEYVALUE_H
#define GENERICDICTIONARY_KEYVALUE_H

template<typename K, typename  V>
class KeyValue
{
private:
    K m_key;
    V m_value;
public:
    K getKey() {return m_key;}
    V getValue() {return m_value;}
    void setValue(V newValue) {m_value = newValue;}

    KeyValue<K, V>& operator=(const KeyValue<K, V>& rhs);

    KeyValue(){};
    KeyValue(K key, V value);
    KeyValue(const KeyValue<K, V>& toBeCopied);
};


template<typename K, typename V>
KeyValue<K, V>& KeyValue<K, V>::operator=(const KeyValue<K, V>& rhs)
{
    this->m_value = rhs.m_value;
    this->m_key = rhs.m_key;
    return *this;
}

template<typename K, typename V>
KeyValue<K, V>::KeyValue(K key, V value):
m_key(key),
m_value(value)
{}

template <typename K, typename V>
KeyValue<K, V>::KeyValue(const KeyValue<K, V>& toBeCopied)
{
    m_key = toBeCopied.m_key;
    m_value = toBeCopied.m_value;
};

#endif //GENERICDICTIONARY_KEYVALUE_H
