#ifndef _STRING_HEADER_INCLUDED_
#define _STRING_HEADER_INCLUDED_

#include <iostream>
#include <cstring>

class String
{
public:
	String();
	String(const char*);
	String(const String&);
	String& operator=(const String&);
	~String();

	void setData(const char*);

	String& operator+=(char);
	String& operator+=(const char*);
	String& operator+=(const String&);

	bool operator==(const String&) const;

	char& operator[](int);
	const char& operator[](int) const;

	friend std::istream& operator>> (std::istream&, String&);
	friend std::ostream& operator<<(std::ostream&, const String&);
	
	const char* getData() const { return m_data; }
	size_t getLen() const { return m_size; }

private:
	void copy(const String&);
	void destroy();

	void resize(size_t);

	static const size_t INITIAL_SIZE = 0;
	static const size_t INITIAL_CAPACITY = 2;

	char* m_data;
	size_t m_size;
	size_t m_capacity;
};

#endif // !_STRING_HEADER_INCLUDED_
