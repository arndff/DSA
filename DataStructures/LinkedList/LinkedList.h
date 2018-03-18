#ifndef _LINKED_LIST_HEADER_INCLUDED_
#define _LINKED_LIST_HEADER_INCLUDED_

template <class T>
class LList
{
public:
	LList();
	LList(const LList&);
	LList& operator=(const LList&);
	~LList();

public:
	void pushBack(const T&);
	void pushFront(const T&);

	void insertAfter(size_t, const T&);

	void removeAll();
	void removeFront();

	void reverse();

	T& getFront() { return m_front->m_data; }
	T& getBack() { return m_back->m_data; }
	const T& getFront() const { return m_front->m_data; }
	const T& getBack() const { return m_back->m_data; }
	
	const T& getAt(size_t) const;
	T& getAt(size_t);
	bool contains(const T&) const;

	void swap(LList&);

	size_t getSize() const { return m_size; }
	bool isEmpty() const { return m_size == 0; }
	
	void print() const;

private:
	void copy(const LList&);

	struct Node
	{
		Node()
			: m_next(nullptr)
		{}
		Node(const T& data, Node* next)
			: m_data(data)
			, m_next(next)
		{}

		public:
			T m_data;
			Node* m_next;
	};

public:
    #include "Iterator.hpp"

	Iterator begin() { return Iterator(m_front); }
	Iterator end() { return Iterator(m_back->m_next); }

	void insertAfter(const Iterator&, const T&);

private:
	Node* m_front;
	Node* m_back;
	size_t m_size;
};

template <class T>
LList<T>::LList()
	: m_front(nullptr)
	, m_back(nullptr)
	, m_size(0)
{}

template <class T>
LList<T>::LList(const LList& rhs)
	: m_front(nullptr)
	, m_back(nullptr)
	, m_size(0)
{
	copy(rhs);
}

template <class T>
LList<T>& LList<T>::operator=(const LList& rhs)
{
	if (this != &rhs)
	{
		removeAll();
		copy(rhs);
	}

	//copy-swap idiom
	/*
	LList<T> tmp(rhs);
	swap(tmp);
	*/

	return *this;
}

template <class T>
LList<T>::~LList()
{
	removeAll();
}

template <class T>
void LList<T>::pushBack(const T& data)
{
	Node* newNode = new Node(data, nullptr);

	if (m_size != 0)
	{
		m_back->m_next = newNode;
		m_back = newNode;
	}
	else
	{
		m_front = m_back = newNode;
	}

	++m_size;
}

template <class T>
void LList<T>::pushFront(const T& data)
{
	if (m_size != 0)
	{
		Node* newNode = new Node(data, m_front);
		m_front = newNode;
	}
	else
	{
		Node* newNode = new Node(data, nullptr);
		m_front = m_back = newNode;
	}

	++m_size;
}

template <class T>
void LList<T>::copy(const LList& rhs)
{
	Node* curr = rhs.m_front;
	while (curr)
	{
		pushBack(curr->m_data);
		curr = curr->m_next;
	}

	m_size = rhs.m_size;
}

template<class T>
void LList<T>::insertAfter(const Iterator& it, const T& data)
{
	if (!it)
	{
		throw std::runtime_error("Iterator not initialized.\n");
	}
	else
	{
		Node* newNode = new Node(data, it.m_pointer->m_next);
		it.m_pointer->m_next = newNode;
	}
}

template <class T>
void LList<T>::insertAfter(size_t idx, const T& data)
{
	if (idx >= m_size) 
	{ 
		throw std::out_of_range("Index out of bounds.\n"); 
	}

	Node* curr = m_front;
	while (idx != 0)
	{
		curr = curr->m_next;
		--idx;
	}

	Node* newNode = new Node(data, curr->m_next);
	curr->m_next = newNode;

	++m_size;
}

template <class T>
void LList<T>::removeAll()
{
	while (m_size != 0)
	{
		removeFront();
	}

	m_front = m_back = nullptr;
}

template <class T>
void LList<T>::removeFront()
{
	if (m_size != 0)
	{
		Node* tmp = m_front;
		m_front = m_front->m_next;
		delete tmp;
		tmp = nullptr;

		--m_size;
	}

	if (m_size == 0)
	{
		m_back = nullptr;
	}
}

template<class T>
void LList<T>::reverse()
{
	if (isEmpty())
		return;

	Node* prev = nullptr;
	Node* curr = m_front;
	Node* next;

	while (curr != nullptr)
	{
		next = curr->m_next;
		curr->m_next = prev;
		prev = curr;
		curr = next;
	}

	m_front = prev;
}

template <class T>
const T& LList<T>::getAt(size_t idx) const
{
	if (idx >= m_size) 
	{ 
		throw std::out_of_range("Index out of bounds.\n"); 
	}
	
	Node* curr = m_front;
	while (idx != 0)
	{
		curr = curr->m_next;
		--idx;
	}

	return curr->m_data;
}

template <class T>
T& LList<T>::getAt(size_t idx)
{
	if (idx >= m_size) 
	{ 
		throw std::out_of_range("Index out of bounds.\n"); 
	}

	Node* curr = m_front;
	while (idx != 0)
	{
		curr = curr->m_next;
		--idx;
	}

	return curr->m_data;
}

template <class T>
bool LList<T>::contains(const T& data) const
{
	Node* curr = m_front;
	while (curr)
	{
		if (curr->m_data == data)
		{
			return true;
		}

		curr = curr->m_next;
	}

	return false;
}

template <class T>
void LList<T>::swap(LList& rhs)
{
	Node* tmp = m_front;
	m_front = rhs.m_front;
	rhs.m_front = tmp;

	tmp = m_back;
	m_back = rhs.m_back;
	rhs.m_back = tmp;
}

template <class T>
void LList<T>::print() const
{
	if (m_size == 0) 
	{ 
		std::cout << "The list is empty.\n";
		return;
	}

	Node* curr = m_front;
	while (curr)
	{
		std::cout << curr->m_data << "\n";
		curr = curr->m_next;
	}
}

#endif // !_LINKED_LIST_HEADER_INCLUDED_
