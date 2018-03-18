#include <iostream>
#include "Dict.h"
#include <cassert>

void test(const char* dict, const char* text)
{
	assert(dict && text);
	std::cout << text << " : ";
	Dict d(dict, text);
}

int main()
{
	test("dict.txt", "text.txt");
	test("dict2.txt", "text2.txt");
	test("dict3.txt", "text3.txt");

	return 0;
}
