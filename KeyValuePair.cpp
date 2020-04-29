#include "pch.h"
#include "KeyValuePair.h"

template <class K, class V>
KeyValuePair<K,V>::KeyValuePair(K key, V value)
{
}

template <class K, class V>
V KeyValuePair<K, V>::getValue()
{
	return V();
}

template <class K, class V>
K KeyValuePair<K, V>::getKey()
{
	return K();
}

template <class K, class V>
void KeyValuePair<K, V>::setKey(K key)
{
}

template <class K, class V>
void KeyValuePair<K, V>::setValue(V value)
{
}
