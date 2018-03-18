#ifndef _LINKED_QUEUE_HEADER_INCLUDED_
#define _LINKED_QUEUE_HEADER_INCLUDED_

template <class T>
class LinkedQueue
{
public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue&);
	LinkedQueue& operator=(const LinkedQueue&);
	~LinkedQueue();

	void enqueue(const T&);
	void dequeue();

	const T& getFront() const { return m_front->m_data; }
	size_t getSize() const { return m_size; }
	
	bool isEmpty() const { return m_size == 0; }
	
	void print() const;

private:
	void copy(const LinkedQueue&);
	void clear();

	struct Node
	{
		Node(const T& data, Node* next = nullptr)
			: m_data(data)
			, m_next(next)
		{}

		T m_data;
		Node* m_next;
	} *m_front, *m_back;

	size_t m_size;
};

template <class T>
LinkedQueue<T>::LinkedQueue()
	: m_front(nullptr)
	, m_back(nullptr)
	, m_size(0)
{}

template <class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& rhs)
	: m_front(nullptr)
	, m_back(nullptr)
	, m_size(0)
{
	copy(rhs);
}

template <class T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue& rhs)
{
	if (this != &rhs)
	{
		clear();
		copy(rhs);
	}

	return *this;
}

template <class T>
LinkedQueue<T>::~LinkedQueue()
{
	clear();
}

template <class T>
void LinkedQueue<T>::enqueue(const T& elem)
{
	Node* newNode = new Node(elem);

	if (!m_front)
	{
		m_front = m_back = newNode;
	}
	else
	{
		m_back->m_next = newNode;
		m_back = newNode;
	}

	++m_size;
}

template <class T>
void LinkedQueue<T>::dequeue()
{
	if (!m_front) 
	{ 
		throw std::runtime_error("The queue is empty.\n");
	}

	if (m_size == 1)
	{
		delete m_front;
		m_front = m_back = nullptr;
	}
	else
	{
		Node* toDelete = m_front;
		m_front = m_front->m_next;
		delete toDelete;
	}

	--m_size;
}

template <class T>
void LinkedQueue<T>::print() const
{
	Node* curr = m_front;
	while (curr)
	{
		std::cout << curr->m_data << " ";
		curr = curr->m_next;
	}
}

template <class T>
void LinkedQueue<T>::copy(const LinkedQueue& rhs)
{
	Node* curr = rhs.m_front;
	while (curr)
	{
		enqueue(curr->m_data);
		curr = curr->m_next;
	}

	m_size = rhs.m_size;
}

template <class T>
void LinkedQueue<T>::clear()
{
	while (m_size != 0)
	{
		dequeue();
	}
}

#endif // !_LINKED_QUEUE_HEADER_INCLUDED_
