#ifndef _LINKED_STACK_HEADER_INCLUDED_
#define _LINKED_STACK_HEADER_INCLUDED_

template <class T>
class LinkedStack
{
public:
	LinkedStack();
	LinkedStack(const LinkedStack&);
	LinkedStack& operator=(const LinkedStack&);
	~LinkedStack();

	void push(const T&);
	void pop();
	
	const T& getTop() const { return m_top->m_data; }
	size_t getSize() const { return m_size; }
	bool isEmpty() const { return m_size == 0; }

	void clear();
	
	void print() const;

private:
	void copy(const LinkedStack&);

	struct Node
	{
		Node(const T& data, Node* next = nullptr)
			: m_data(data)
			, m_next(next)
		{}

		T m_data;
		Node* m_next;

	} *m_top;

	size_t m_size;
};

template <class T>
LinkedStack<T>::LinkedStack()
	: m_top(nullptr)
	, m_size(0)
{}

template <class T>
LinkedStack<T>::LinkedStack(const LinkedStack& rhs)
	: m_top(nullptr)
{
	copy(rhs);
}

template <class T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack& rhs)
{
	if (this != &rhs)
	{
		clear();
		copy(rhs);
	}

	return *this;
}

template <class T>
LinkedStack<T>::~LinkedStack()
{
	clear();
}

template <class T>
void LinkedStack<T>::push(const T& data)
{
	Node* newNode = new Node(data, m_top);
	m_top = newNode;

	++m_size;
}

template <class T>
void LinkedStack<T>::pop()
{
	if (!m_top) 
	{ 
		throw std::runtime_error("The stack is empty.\n"); 
	}

	Node* oldTop = m_top;
	m_top = m_top->m_next;
	
	delete oldTop;

	--m_size;
}

template <class T>
void LinkedStack<T>::clear()
{
	while (m_size != 0)
	{
		pop();
	}

	m_top = nullptr;
}

template <class T>
void LinkedStack<T>::print() const
{
	if (!m_top) 
	{ 
		std::cout << "The stack is empty.\n";
		return;
	}

	Node* curr = m_top;
	while (curr)
	{
		std::cout << curr->m_data << " ";
		curr = curr->m_next;
	}

	std::cout << "\n\n";
}

template <class T>
void LinkedStack<T>::copy(const LinkedStack& rhs)
{
	//first, copy rhs's elements in temporary stack
	LinkedStack tmp;
	Node* curr = rhs.m_top;
	
	while (curr)
	{
		tmp.push(curr->m_data);
		curr = curr->m_next;
	}

	tmp.m_size = rhs.m_size;

	//then, copy tmp's elements in our stack
	curr = tmp.m_top;

	while (curr)
	{
		push(curr->m_data);
		curr = curr->m_next;
	}

	m_size = tmp.m_size;
}

#endif // !_LINKED_STACK_HEADER_INCLUDED_
