#include <iostream>
#include <cassert>
#include "Parser.h"

void printResult(const Parser& parser)
{
	String res = parser.getPostfix();
	std::cout << res;
	parser.printResult();
}

void test(const char* expr, const char* oprtrs)
{
	assert(expr && oprtrs);

	Parser parser(expr, oprtrs);
	printResult(parser);

	std::cout << "\n\n\n";
}

int main()
{
	test("expression.txt", "operators.txt");
	test("expression2.txt", "operators2.txt");

	return 0;
}