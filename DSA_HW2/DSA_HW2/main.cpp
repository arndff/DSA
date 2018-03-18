#include <iostream>
#include <cassert>
#include "Elevator.h"

void test(const char* path)
{
	assert(path);
	
	Elevator e(path);
	e.processQueries();

	std::cout << "\n\n\n";
}

int main()
{
	test("10-10-0-input.txt");
	test("100-1000-1-input.txt");
	
	return 0;
}