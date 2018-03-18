#ifndef HASH_TABLE_HEADER_INCLUDED__
#define HASH_TABLE_HEADER_INCLUDED__

#include <vector>

template <class KeyType>
using hashFnType = size_t(*) (const KeyType&, size_t);

template <class KeyType, class ValueType>
class HashTable
{
public:
	HashTable(hashFnType<KeyType>, size_t);

	void insert(const KeyType&, const ValueType&);
	bool search(const KeyType&) const;
	void remove(const KeyType&);

	ValueType& operator[] (const KeyType&);
	const ValueType& operator[] (const KeyType&) const;

private:
	struct KeyValue
	{
		KeyValue(const KeyType& key, const ValueType& value)
			: m_key(key)
			, m_value(value)
		{}

		KeyType m_key;
		ValueType m_value;
	};

	void resize(size_t);
	static const double RESIZE_FACTOR;
	static const size_t INITIAL_SIZE = 0;

	std::vector< std::vector<KeyValue> > m_table;
	hashFnType<KeyType> m_hash;
	size_t m_size; //count of added pairs
	size_t m_capacity;
};

template<class KeyType, class ValueType>
const double HashTable<KeyType, ValueType> ::RESIZE_FACTOR = 0.75;

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(hashFnType<KeyType> hash, size_t capacity)
	: m_table(capacity)
	, m_hash(hash)
	, m_size(INITIAL_SIZE)
	, m_capacity(capacity)
{}

template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
	if (m_size / (float)m_capacity > RESIZE_FACTOR)
	{
		resize(m_capacity*2);
	}

	size_t idx = m_hash(key, m_capacity);

	for (KeyValue& pair : m_table[idx])
	{
		if (pair.m_key == key)
		{
			pair.m_value = value;
			return;
		}
	}

	//if the table doesn't contain current key,
	//then simply adds a new pair in the table
	KeyValue newPair(key, value);
	m_table[idx].push_back(newPair);
	++m_size;
}

template <class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::search(const KeyType& key) const
{
	size_t idx = m_hash(key, m_capacity);

	for (const KeyValue& pair : m_table[idx])
	{
		if (pair.m_key == key)
		{
			return true;
		}
	}

	return false;
}

template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::remove(const KeyType& key)
{
	size_t idx = m_hash(key, m_capacity);

	for (KeyValue& pair : m_table[idx])
	{
		if (pair.m_key == key)
		{
			m_table[idx].erase(pair);
			--m_size;

			return;
		}
	}

	throw std::logic_error("No such key exists.\n");
}

template <class KeyType, class ValueType>
ValueType& HashTable<KeyType, ValueType>::operator[] (const KeyType& key)
{
	size_t idx = m_hash(key, m_capacity);

	for (KeyValue& pair : m_table[idx])
	{
		if (pair.m_key == key)
		{
			return pair.m_value;
		}
	}

	throw std::logic_error("No such key exists.\n");
}

template <class KeyType, class ValueType>
const ValueType& HashTable<KeyType, ValueType>::operator[] (const KeyType& key) const
{
	size_t idx = m_hash(key, m_capacity);

	for (const KeyValue& pair : m_table[idx])
	{
		if (pair.m_key == key)
		{
			return pair.m_value;
		}
	}

	throw std::logic_error("No such key exists.\n");
}

template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::resize(size_t newCapacity)
{
	std::vector < std::vector<KeyValue> > newTable(newCapacity);

	for (size_t i = 0; i < m_table.size(); ++i)
	{
		for (const KeyValue& pair : m_table[i])
		{
			newTable[m_hash(pair.m_key, newCapacity)].push_back(pair);
		}
	}

	m_table.swap(newTable); //O(1)

	m_capacity *= 2;
}

#endif // !HASH_TABLE_HEADER_INCLUDED__
