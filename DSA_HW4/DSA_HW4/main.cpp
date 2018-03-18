#include <iostream>
#include "Parser.h"
#include <cassert>

void testParser(const char* path)
{
	assert(path);
	Parser(path);
}

int main()
{
	testParser("TestFile.dat");

	return 0;
}
