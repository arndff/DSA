#ifndef _VECTOR_HEADER_INCLUDED_
#define _VECTOR_HEADER_INCLUDED_

static const size_t INITIAL_SIZE = 0;
static const size_t INITIAL_CAPACITY = 2;

template <class T>
class Vector
{
	//голяма четворка
public:
	Vector();
	Vector(const Vector&);
	Vector<T>& operator=(const Vector&);
	~Vector();

public:
	//добавя елемент в края
	void push_back(const T&);

	//премахва елемент от дадена позиция
	void remove(size_t);

	//връща елемент на дадена позиция
	const T& getAt(size_t) const;

	//проверява дали векторът съдържа даден елемент
	bool contains(const T&) const;

	void destroy();

public:
	const T& operator[](int) const;
	T& operator[](int);

public:
	size_t getSize() const { return m_size; }
	size_t getCapacity() const { return m_capacity; }
	bool isEmpty() const { return m_size == 0; }

#include "Iterator.hpp"

const Iterator begin() const { return Iterator(m_data); }
Iterator begin() { return Iterator(m_data); }
const Iterator end() const { return Iterator(m_data + m_size); }
Iterator end() { return Iterator(m_data + m_size); }

private:
	void copy(const Vector&);
	void resize(size_t);
	T* allocate(T*&, size_t) const;

private:
	T* m_data;
	size_t m_size, m_capacity;
};

//голяма четворка

template <class T>
Vector<T>::Vector()
	: m_data(nullptr)
	, m_size(INITIAL_SIZE)
	, m_capacity(INITIAL_CAPACITY)
{
	m_data = allocate(m_data, m_capacity);
}

template <class T>
Vector<T>::Vector(const Vector& rhs)
	: m_data(nullptr)
{
	copy(rhs);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
	if (this != &rhs)
	{
		destroy();
		copy(rhs);
	}

	return *this;
}

template <class T>
Vector<T>::~Vector()
{
	destroy();
}

//други

template <class T>
void Vector<T>::push_back(const T& elem)
{
	if (m_size == m_capacity)
	{
		resize( m_size ? 2 * m_size : INITIAL_CAPACITY);
	}

	m_data[m_size++] = elem;
}

template<class T>
void Vector<T>::remove(size_t idx)
{
	if (idx >= m_size) { throw std::out_of_range("Index out of bounds!\n"); }

	m_data[idx] = m_data[m_size - 1];
	--m_size;

	/*

	//друг подход, обаче за O(n) време,
	//като горният е за O(1),
	//но НЕ запазва наредбата на елементите
	
	for (size_t i = index; i < size - 1; ++i)
        data[i] = data[i + 1];
    --size;
	
	*/
	
	if (2 * (m_size + 1) == m_capacity) 
	{ 
		resize(m_size + 1); 
	}
}

template<class T>
const T& Vector<T>::getAt(size_t idx) const
{
	if (idx >= m_size) { throw std::out_of_range("Index out of bounds!\n"); }

	return m_data[idx];
}

template<class T>
bool Vector<T>::contains(const T& elem) const
{
	for (size_t i = 0; i < m_size; ++i)
	{
		if (m_data[i] == elem)
		{
			return true;
		}
	}

	return false;
}

template<class T>
const T& Vector<T>::operator[](int idx) const
{
	if (idx >= m_size) { throw std::out_of_range("Index out of bounds!\n"); }

	return m_data[idx];
}

template<class T>
T& Vector<T>::operator[](int idx)
{
	if (idx >= m_size) { throw std::out_of_range("Index out of bounds!\n"); }
	
	return m_data[idx];
}

//частни методи

template<class T>
void Vector<T>::copy(const Vector& rhs)
{
	m_data = allocate(m_data, rhs.m_capacity);

	for (size_t i = 0; i < rhs.m_size; ++i)
	{
		m_data[i] = rhs.m_data[i];
	}

	m_size = rhs.m_size;
	m_capacity = rhs.m_capacity;
}

template<class T>
void Vector<T>::destroy()
{
	delete[] m_data;
	m_data = nullptr; //
	m_size = m_capacity = 0;
}

template<class T>
void Vector<T>::resize(size_t new_capacity)
{
	T* tmp_data = allocate(tmp_data, new_capacity);

	for (size_t i = 0; i < m_size; ++i)
	{
		tmp_data[i] = m_data[i];
	}

	m_data = tmp_data;
	m_capacity = new_capacity;
}

template <class T>
T* Vector<T>::allocate(T*& dest, size_t size) const
{
	try
	{
		dest = new T[size];
	}
	catch (std::bad_alloc&)
	{
		throw std::runtime_error("Memory allocation problem!\n");
	}

	return dest;
}

#endif _VECTOR_HEADER_INCLUDED_