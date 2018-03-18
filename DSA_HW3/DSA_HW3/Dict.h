#ifndef _DICT_HEADER_INCLUDED_
#define _DICT_HEADER_INCLUDED_

#include "Trie.h"
#include "String.h"
#include <fstream>

class Dict
{
public:
	Dict(const char*, const char*);

	Dict(const Dict&) = delete;
	Dict& operator=(const Dict&) = delete;

private:
	void parseDict(std::ifstream&);
	void extractWord(std::ifstream&, String&, char&) const;

	void evaluateTxt(std::ifstream&);
	size_t countWords(std::ifstream&) const;
	bool isLetter(char c) const;

	Trie dict;
	size_t MAX_PHRASE_LEN;
};

#endif // !_DICT_HEADER_INCLUDED_
