#pragma once
#include <map>

template <class K, class V>
class KeyValuePair
{
private:
	KeyValuePair<K,V> elements;
public:
	KeyValuePair(K key, V value);
	V getValue();
	K getKey();
	void setKey(K key);
	void setValue(V value);
};
