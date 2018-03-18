#ifndef _DOUBLY_LINKED_LIST_HEADER_INCLUDED_
#define _DOUBLY_LINKED_LIST_HEADER_INCLUDED_

template <class T>
class DLList
{
public:
	DLList();
	DLList(const DLList&);
	DLList& operator=(const DLList&);
	~DLList();

public:
	const T& getHead() const { return m_head->m_data; }
	const T& getTail() const { return m_tail->m_data; }

	void addHead(const T&);
	void addTail(const T&);

	void insertAfter(size_t, const T&);
	void insertBefore(size_t, const T&);

	void removeAll();
	void removeHead();
	void removeTail();

	const T& getAt(size_t) const;
	T& getAt(size_t);
	void setAt(size_t, const T&);

	bool contains(const T&) const;

	void swap(DLList&);

	size_t getSize() const { return m_size; }
	bool isEmpty() const { return m_size == 0; }

	void print() const;

private:
	struct Node
	{
		Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
			: m_data(data)
			, m_prev(prev)
			, m_next(next)
		{}

		T m_data;
		Node* m_prev;
		Node* m_next;
	};
 
#include "Iterator.hpp"

public:
	Iterator begin() { return Iterator(m_head); }
	Iterator end() { return Iterator(m_tail->m_next); }

private:
	void copy(const DLList&);

private:
	Node* m_head;
	Node* m_tail;
	size_t m_size;
};

template <class T>
DLList<T>::DLList()
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{}

template <class T>
DLList<T>::DLList(const DLList& rhs)
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{
	copy(rhs);
}

template <class T>
DLList<T>& DLList<T>::operator=(const DLList& rhs)
{
	DLList<T> tmp(rhs);
	swap(tmp);

	return *this;
}

template <class T>
DLList<T>::~DLList()
{
	removeAll();

	m_head = m_tail = nullptr;
}

template <class T>
void DLList<T>::addHead(const T& data)
{
	if (!m_head)
	{
		Node* newNode = new Node(data);
		m_head = m_tail = newNode;
	}
	else
	{
		Node* newNode = new Node(data, nullptr, m_head);
		m_head->m_prev = newNode; //[42]<-
		m_head = newNode;
	}

	++m_size;
}

template <class T>
void DLList<T>::addTail(const T& data)
{
	if (!m_head)
	{
		Node* newNode = new Node(data);
		m_head = m_tail = newNode;
	}
	else
	{
		Node* newNode = new Node(data, m_tail, nullptr);
		m_tail->m_next = newNode; //->[42]
		m_tail = newNode;
	}

	++m_size;
}

template <class T>
void DLList<T>::insertAfter(size_t idx, const T& data)
{
	if (idx >= m_size) 
	{ 
		throw std::out_of_range("Index out of bounds!\n"); 
	}

	Node* curr = m_head;
	while (idx != 0)
	{
		curr = curr->m_next;
		--idx;
	}

	Node* newNode = new Node(data, curr, curr->m_next);
	//cover the case when curr is the tail of the dllist
	if (curr->m_next)
	{
		//if curr isn't the last element, we do this:
		curr->m_next->m_prev = newNode; //[42]<-
	}
	
	curr->m_next = newNode; //->[42]

	++m_size;
}

template <class T>
void DLList<T>::insertBefore(size_t idx, const T& data)
{
	if (idx == 1)
	{
		addHead(data);
	}
	else
	{
		insertAfter(idx - 1, data);
	}
}

template <class T>
void DLList<T>::removeAll()
{
	size_t cnt = m_size;

	while(cnt != 0)
	{
		--cnt;	
		removeHead(); q
	}

	m_head = m_tail = nullptr;
}

template <class T>
void DLList<T>::removeHead()
{
	if (!m_head)
	{
		throw std::runtime_error("The list is empty.\n");
	}
	
	
	Node* oldHead = m_head;
	if (m_head->m_next)
	{
		m_head->m_next->m_prev = nullptr;
		m_head = m_head->m_next;
		delete oldHead;
	}
	//cover the case when m_size = 1
	else
	{
		delete m_head;
		m_head = nullptr;
	}

	--m_size;
}

template <class T>
void DLList<T>::removeTail() 
{
	if (!m_tail)
	{
		throw std::runtime_error("The list is empty.\n");
	}

	Node* oldTail = m_tail;
	if (m_tail->m_prev)
	{
		m_tail->m_prev->m_next = nullptr;
		m_tail = m_tail->m_prev;
		delete oldTail;
	}
	//cover the case when m_size = 1
	else
	{
		delete m_tail;
		m_tail = nullptr;
	}

	--m_size;
}

template <class T>
const T& DLList<T>::getAt(size_t idx) const
{
	if (idx >= m_size) 
	{ 
		throw std::out_of_range("Index out of bounds.\n"); 
	}

	Node* curr = m_head;
	while (idx != 0)
	{
		curr = curr->m_next;
		--idx;
	}

	return curr->m_data;
}

template <class T>
T& DLList<T>::getAt(size_t idx)
{
	if (idx >= m_size) 
	{ 
		throw std::out_of_range("Index out of bounds.\n"); 
	}

	Node* curr = m_head;
	while (idx != 0)
	{
		curr = curr->m_next;
		--idx;
	}

	return curr->m_data;
}

template <class T>
void DLList<T>::setAt(size_t idx, const T& data)
{
	if (idx == 0) 
	{ 
		addHead(data); 
	}
	else
	{
		insertAfter(idx - 1, data);
	}
}

template<class T>
bool DLList<T>::contains(const T& data) const
{
	if (!m_head)
	{
		throw std::runtime_error("The list is empty.\n");
	}
	else
	{
		Node* curr = m_head;
		while (curr)
		{
			if (curr->m_data == data)
			{
				return true;
			}

			curr = curr->m_next;
		}
	}

	return false;
}

template <class T>
void DLList<T>::swap(DLList& rhs)
{
	Node* tmpHead = m_head;
	m_head = rhs.m_head;
	rhs.m_head = tmpHead;

	Node* tmpTail = m_tail;
	m_tail = rhs.m_tail;
	rhs.m_tail = tmpTail;
}

template <class T>
void DLList<T>::print() const
{
	if (!m_head)
	{
		std::cout << "The list is empty.\n";
		return;
	}
	else
	{
		Node* curr = m_head;
		while (curr)
		{
			std::cout << curr->m_data << " ";
			curr = curr->m_next;
		}
	}
}

template <class T>
void DLList<T>::copy(const DLList& rhs)
{
	Node* curr = rhs.m_head;
	while (curr)
	{
		addTail(curr->m_data);
		curr = curr->m_next;
	}
}

#endif // !_DOUBLY_LINKED_LIST_HEADER_INCLUDED_
