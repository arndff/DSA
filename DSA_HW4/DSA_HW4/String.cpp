#include "String.h"

String::String()
	: m_data(nullptr)
	, m_size(INITIAL_SIZE)
	, m_capacity(INITIAL_CAPACITY)
{
	m_data = new char[m_capacity + 1];
	strcpy(m_data, ""); //initialize the data with the empty string
}

String::String(const char* str)
	: m_data(nullptr)
	, m_size(INITIAL_SIZE)
	, m_capacity(INITIAL_CAPACITY)
{
	if (!str)
	{
		throw std::runtime_error("Invalid string has been passed.\n");
	}
	else
	{
		setData(str);

		m_size = strlen(str);
		m_capacity = 2*m_size + 1;
	}
}

String::String(const String& rhs)
	: m_data(nullptr)
	, m_size(INITIAL_SIZE)
	, m_capacity(INITIAL_CAPACITY)
{
	copy(rhs);
}

String& String::operator=(const String& rhs)
{
	if (this != &rhs)
	{
		destroy();
		copy(rhs);
	}

	return *this;
}

String::~String()
{
	destroy();
}

void String::setData(const char* str)
{
	m_data = new char[2 * strlen(str) + 1]; //"string\0"+"string"
	strcpy(m_data, str);
}

String& String::operator+=(char symbol)
{
	//if the object's content was destroyed... and we want to use the same object again
	//set its size to 2*INITIAL_CAPACITY + 1
	if (m_size == 0 && m_capacity == 0) 
	{ 
		resize(2 * INITIAL_CAPACITY + 1); 
	}
	
	if (m_size + 1 == m_capacity) { resize(2 * m_size + 1); }
	//           ^                                      ^ 
	//         '\0'                                   '\0'

	m_data[m_size++] = symbol;
	m_data[m_size] = '\0';
	
	return *this;
}

String& String::operator+=(const char* str)
{
	size_t len = strlen(str);

	for (size_t i = 0; i < len; ++i)
	{
		(*this) += str[i]; //using +=(char)
	}

	return *this;
}

String& String::operator+=(const String& rhs)
{
	(*this) += rhs.m_data; //using +=(const char*)

	return *this;
}

bool String::operator==(const String& rhs) const
{
	return strcmp(m_data, rhs.m_data) == 0;
}

void String::copy(const String& rhs)
{
	m_data = new char[rhs.m_capacity];
	strcpy(m_data, rhs.m_data);

	m_size = rhs.m_size;
	m_capacity = rhs.m_capacity;
}

void String::destroy()
{
	delete[] m_data;
	m_data = nullptr;
	m_size = m_capacity = 0;
}

void String::resize(size_t newCap)
{
	char* tmp = new char[newCap + 1];

	if (m_data) 
	{ 
		strcpy(tmp, m_data); 
	} //if m_size==m_capacity==0, nothing to copy
	
	delete[] m_data; //!!! leak otherwise
	m_data = tmp;
	m_capacity = newCap;
}

char& String::operator[](int idx)
{
	return m_data[idx];
}

const char& String::operator[](int idx) const
{
	return m_data[idx];
}

std::istream &operator>> (std::istream& in, String& str)
{
	while (in.peek() != ' ' && in.peek() != '\t')
	{
		str += in.get();
		if (in.eof()) { break; }
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
	out << str.m_data;
	return out;
}