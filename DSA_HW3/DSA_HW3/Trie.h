#ifndef _TRIE_HEADER_INCLUDED_
#define _TRIE_HEADER_INCLUDED_

#include <iostream>
#include "String.h"

class Trie
{
public:
	Trie();
	Trie(const Trie&);
	Trie& operator=(const Trie&);
	~Trie();

	void insert(const String&, int);
	bool search(const String&, int&) const;

	size_t getSize() const { return m_size; }

private:
	static const size_t ALPHABET_SIZE = 27; //+ 1 because we can have a phrase, so the last idx will stand for space ' '

	struct Node
	{
		Node* m_children[ALPHABET_SIZE];
		int m_coeff; //could be a negative one
		bool m_isEndOfWord; //a var which indicates the end of a word
	} *m_root;

	void insert(Node*&, const String&, size_t&, int);
	void insertHelper(size_t, Node*&, const String&, size_t&, int);

	bool search(const Node*, const String&, size_t&, int&) const;
	bool searchHelper(size_t, const Node*, const String&, size_t&, int&) const;

	void init(Node*);
	void copy(Node*, Node*);
	void destroy(Node*&);

	size_t m_size;
};

#endif // !_TRIE_HEADER_INCLUDED_
