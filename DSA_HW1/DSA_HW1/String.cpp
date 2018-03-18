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
		m_data = new char[2*strlen(str) + 1]; //"string\0"+"string"
		strcpy(m_data, str);

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

String& String::operator+=(char symbol)
{
	if (m_size + 1 == m_capacity) { resize(2 * m_size + 1); }
	//           ^                                      ^ 
	//         '\0'                                   '\0'

	m_data[m_size++] = symbol;
	m_data[m_size] = '\0';
	
	return *this;
}

String& String::operator+=(const char* str)
{
	size_t cnt = m_size,
		   len = strlen(str);

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

char& String::operator[](int idx)
{
	assert(idx < m_size);
	return m_data[idx];
}

const char& String::operator[](int idx) const
{
	assert(idx < m_size);
	return m_data[idx];
}

bool String::operator==(const String& rhs) const
{
	return strcmp(m_data, rhs.m_data) == 0;
}

std::ostream& operator<<(std::ostream& out, const String& obj)
{
	out << obj.m_data << "\n";

	return out;
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
	m_size = m_capacity = 0;
}

void String::resize(size_t newCap)
{
	char* tmp;
	tmp = new char[newCap + 1];

	strcpy(tmp, m_data);
	
	delete[] m_data; //!!! leak otherwise
	m_data = tmp;
	m_capacity = newCap;
}