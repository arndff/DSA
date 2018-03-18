#ifndef _PARSER_HEADER_INCLUDED_
#define _PARSER_HEADER_INCLUDED_

#include "Pair.h"
#include "String.h"
#include "BST.h"

#include <fstream>
#include <cassert>

class Parser
{
public:
	Parser(const char*);

private:
	void extractData(std::ifstream&);
	void menu();

	BST<int, String> m_tree;
};

#endif // !_PARSER_HEADER_INCLUDED_