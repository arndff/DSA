#ifndef _PAIR_HEADER_INCLUDED_
#define _PAIR_HEADER_INCLUDED_

#include <fstream>
#include "String.h"

template <class KeyType, class DataType>
class Pair
{
public:
	Pair()
		: m_key(-1)
	{}

	Pair(const KeyType& key, const DataType& data)
		: m_key(key)
		, m_data(data)
	{}

	const KeyType& getKey() const { return m_key; }
	const DataType& getData() const { return m_data; }

	friend std::ostream& operator<<(std::ostream&, const Pair&);

private:
	KeyType m_key;
	DataType m_data;
};

//predefined operators
template <class KeyType, class DataType>
std::ostream& operator<<(std::ostream& out, const Pair<KeyType, DataType>& p)
{
	out << p.getKey() << " " << p.getData() << "\n";
	return out;
}

template <class KeyType, class DataType>
bool operator==(const Pair<KeyType, DataType>& p1, const Pair<KeyType, DataType>& p2)
{
	return p1.getKey() == p2.getKey();
}

template <class KeyType, class DataType>
bool operator!=(const Pair<KeyType, DataType>& p1, const Pair<KeyType, DataType>& p2)
{
	return !(p1 == p2);
}

template <class KeyType, class DataType>
bool operator<(const Pair<KeyType, DataType>& p1, const Pair<KeyType, DataType>& p2)
{
	return p1.getKey() < p2.getKey();
}

template <class KeyType, class DataType>
bool operator>(const Pair<KeyType, DataType>& p1, const Pair<KeyType, DataType>& p2)
{
	return !(p1 == p2 || p1 < p2);
}

#endif // !_PAIR_HEADER_INCLUDED_
