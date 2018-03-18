#ifndef __LINKED_LIST_ITERATOR_
#define __LINKED_LIST_ITERATOR_

class Iterator
{
	friend class LList;

public:
	T& operator*() { return m_pointer->m_data; }
	const T& operator*() const { return m_pointer->m_data; }
	
	T* operator->() { return &m_pointer->m_data; }
	const T* operator->() const { return &m_pointer->m_data; }
	
	Iterator& operator++()
	{
		m_pointer = m_pointer->m_next;	
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator res(*this);
		++(*this);
		return res;
	}

	bool operator==(const Iterator& rhs)
	{
		return m_pointer == rhs.m_pointer;
	}

	bool operator!=(const Iterator& rhs)
	{
		return !(*this == rhs);
	}

	operator bool() const
	{
		return m_pointer != nullptr;
	}

private:
	Iterator(Node* pointer) : m_pointer(pointer) {}

	Node* m_pointer;
};

#endif // !__LINKED_LIST_ITERATOR_
