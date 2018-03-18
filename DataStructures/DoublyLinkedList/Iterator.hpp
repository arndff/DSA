#ifndef _ITERATOR_HEADER_INCLUDED_
#define _ITERATOR_HEADER_INCLUDED_

class Iterator
{
	friend class DLList;

public:
	T& operator*() { return m_ptr->m_data; }
	const T& operator*() const { return m_ptr->m_data; }
	T* operator->() { return &m_ptr->m_data; }
	const T* operator->() const { return &m_ptr->m_data; }

	Iterator& operator++()
	{
		m_ptr = m_ptr->m_next;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator res(*this);
		++res;
		return res;
	}

	Iterator& operator--()
	{
		m_ptr = m_ptr->m_prev;
		return *this;
	}

	Iterator operator--(int)
	{
		Iterator res(*this);
		--res;
		return res;
	}

	bool operator==(const Iterator& rhs) const
	{
		return m_ptr == rhs.m_ptr;
	}

	bool operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	bool operator() const
	{
		return m_pointer != nullptr;
	}

private:
	Iterator(Node* ptr) :m_ptr(ptr) {}

	Node* m_ptr;
};


#endif // !_ITERATOR_HEADER_INCLUDED_
