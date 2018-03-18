#ifndef _STACK_HEADER_INCLUDED_
#define _STACK_HEADER_INCLUDED_

template <class T>
class Stack
{
public:
	Stack();
	Stack(const Stack&);
	Stack& operator=(const Stack&);
	~Stack();

	void push(const T&);
	void pop();
	
	const T& getTop() const { return m_top->m_data; }
	size_t getSize() const { return m_size; }
	bool isEmpty() const { return m_size == 0; }

	void clear();

	void print() const;

private:
	void copy(const Stack&);
	

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
Stack<T>::Stack()
	: m_top(nullptr)
	, m_size(0)
{}

template <class T>
Stack<T>::Stack(const Stack& rhs)
	: m_top(nullptr)
{
	copy(rhs);
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	if (this != &rhs)
	{
		clear();
		copy(rhs);
	}

	return *this;
}

template <class T>
Stack<T>::~Stack()
{
	clear();
}

template <class T>
void Stack<T>::push(const T& data)
{
	Node* newNode = new Node(data, m_top);
	m_top = newNode;

	++m_size;
}

template <class T>
void Stack<T>::pop()
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
void Stack<T>::print() const
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
void Stack<T>::copy(const Stack& rhs)
{
	//first, copy rhs's elements in temporary stack
	Stack tmp;
	Node* curr = rhs.m_top;
	
	while (curr)
	{
		tmp.push(curr->m_data);
		curr = curr->m_next;
	}

	//then, copy tmp's elements in our stack
	curr = tmp.m_top;

	while (curr)
	{
		push(curr->m_data);
		curr = curr->m_next;
	}

	m_size = tmp.m_size;
}

template <class T>
void Stack<T>::clear()
{
	while (m_size != 0)
	{
		pop();
	}

	m_top = nullptr;
}

#endif // !_STACK_HEADER_INCLUDED_