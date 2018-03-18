#ifndef _ITERATOR_HEADER_INCLUDED_
#define _ITERATOR_HEADER_INCLUDED_

class Iterator
{
	friend class Vector; //(!)

public:
	T& operator* ()
	{
		return *m_ptr;
	}
	const T& operator* () const
	{
		return *m_ptr;
	}
	T* operator-> ()
	{
		return m_ptr;
	}
	const T* operator-> () const
	{
		return m_ptr;
	}
	Iterator& operator++()
	{
		++m_ptr;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator res(*this);
		++(*this);
		return res;
	}
	Iterator& operator--()
	{
		--m_ptr;
		return *this;
	}
	Iterator operator--(int)
	{
		Iterator res(*this);
		--(*this);
		return res;
	}

public:
	bool operator==(const Iterator& rhs) const
	{
		return m_ptr == rhs.m_ptr;
	}

	bool operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	bool operator<(const Iterator& rhs) const
	{
		return m_ptr < rhs.m_ptr;
	}

	bool operator>(const Iterator& rhs) const
	{
		return rhs < *this;
	}

	bool operator>=(const Iterator& rhs) const
	{
		return *this > rhs || *this == rhs;
	}

private:
	Iterator(T* ptr) : m_ptr(ptr) {}

	T* m_ptr;
};

#endif // !_ITERATOR_HEADER_INCLUDED_