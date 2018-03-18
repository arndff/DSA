#ifndef _ARRAY_STACK_HEADER_INCLUDED_
#define _ARRAY_STACK_HEADER_INCLUDED_

#include "Vector.h"

template <class T>
class ArrayStack
{
public:
	void push(const T&);
	void pop();
	
	const T& getTop() const { return arr[arr.getSize() - 1]; };
	T& getTop() { return arr[arr.getSize() - 1]; };
	size_t getSize() const { return arr.getSize(); }
	
	bool isEmpty() const { return arr.getSize() == 0; }

	void print() const;

private:
	Vector<T> arr;
};

template <class T>
void ArrayStack<T>::push(const T& data)
{
	arr.push_back(data);
}

template <class T>
void ArrayStack<T>::pop()
{
	arr.remove(arr.getSize() - 1);
}

template <class T>
void ArrayStack<T>::print() const
{
	auto it = arr.end();
	--it;

	for ( ; it >= arr.begin(); --it)
	{
		std::cout << *it << " ";
	}

	std::cout << "\n\n";
}

#endif // _ARRAY_STACK_HEADER_INCLUDED_

