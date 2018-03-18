#ifndef _CIRCULAR_QUEUE_HEADER_INCLUDED_
#define _CIRCULAR_QUEUE_HEADER_INCLUDED_

#include <iostream>

template <class T>
class CircularQueue
{
public:
	CircularQueue(size_t newCap = INITIAL_CAPACITY);
	CircularQueue(const CircularQueue&);
	CircularQueue& operator=(const CircularQueue&);
	~CircularQueue();

	void enqueue(const T&);
	void dequeue();

	const T& getFront() const { return m_arr[m_front]; }
	size_t getSize() const { return m_size; }

	bool isEmpty() const { return m_size == 0; }
	
	void print() const;

private:
	void copy(const CircularQueue&);
	void clear();
	void resize(size_t);
	T* allocate(size_t);

	static const size_t INITIAL_SIZE = 0;
	static const size_t INITIAL_CAPACITY = 2;
	static const int INVALID_INDEX = -1;

	T* m_arr;
	size_t m_size, m_capacity;
	size_t m_front, m_rear;
};

template <class T>
CircularQueue<T>::CircularQueue(size_t newCap = INITIAL_CAPACITY)
	: m_size(INITIAL_SIZE)
	, m_capacity(newCap)
	, m_front(INVALID_INDEX)
	, m_rear(INVALID_INDEX)
{
	m_arr = allocate(m_capacity);
}

template <class T>
CircularQueue<T>::CircularQueue(const CircularQueue& rhs)
	: CircularQueue(rhs.m_capacity)
{
	copy(rhs);
}

template <class T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue& rhs)
{
	if (this != &rhs)
	{
		clear();
		m_arr = allocate(rhs.m_capacity);
		m_capacity = rhs.m_capacity;
		copy(rhs);
	}

	return *this;
}

template <class T>
CircularQueue<T>::~CircularQueue()
{
	clear();
}

template <class T>
void CircularQueue<T>::enqueue(const T& elem)
{
	if (m_size == m_capacity) 
	{ 
		resize(2 * m_size);
	}

	if (isEmpty())
	{
		m_front = m_rear = 0;
		m_arr[m_front] = elem;
	}
	else
	{
		m_rear = (m_rear + 1) % m_capacity;
		m_arr[m_rear] = elem;
	}

	++m_size;
}

template <class T>
void CircularQueue<T>::dequeue()
{
	if (m_front == m_rear)
	{
		m_front = m_rear = -1;
	}
	else
	{
		m_front = (m_front + 1) % m_capacity;
	}
	
	--m_size;
}

template <class T>
void CircularQueue<T>::print() const
{
	size_t curr = 0;

	for (size_t i = m_front; curr < m_size; i = (i+1) % m_capacity)
	{
		++curr;
		std::cout << m_arr[i] << " ";
	}

	std::cout << "\n";
}

template <class T>
void CircularQueue<T>::copy(const CircularQueue& rhs)
{
	size_t curr = 0;
	for (size_t i = rhs.m_front; curr < rhs.m_size; i = (i + 1) % rhs.m_capacity)
	{
		++curr;
		enqueue(rhs.m_arr[i]);
	}
}

template <class T>
void CircularQueue<T>::clear()
{
	delete[] m_arr;
	m_size = m_capacity = 0;
	m_front = m_rear = INVALID_INDEX;
}

template <class T>
void CircularQueue<T>::resize(size_t newCap)
{
	T* tmp = allocate(newCap);
	size_t i = 0;
	
	while (!isEmpty())
	{
		tmp[i++] = getFront();
		dequeue();
	}

	delete[] m_arr;
	m_arr = tmp;
	m_size = i;
	m_capacity = newCap;

	m_front = 0;
	m_rear = m_size - 1;
}

template <class T>
T* CircularQueue<T>::allocate(size_t capacity)
{
	T* res = new T[capacity];
	
	return res;
}

#endif // !_CIRCULAR_QUEUE_HEADER_INCLUDED_

