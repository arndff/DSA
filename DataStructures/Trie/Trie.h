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

	void insert(const String&);
	bool search(const String&) const;

	size_t getSize() const { return m_size; }

private:
	//26+1, reason: phrase support (last index stands for space ' ')
	static const size_t ALPHABET_SIZE = 27;

	struct Node
	{
		Node* m_children[ALPHABET_SIZE];
		bool m_isEndOfWord;
	} *m_root;

	void insert(Node*&, const String&, size_t&);
	void insertHelper(size_t, Node*&, const String&, size_t&);

	bool search(const Node*, const String&, size_t&) const;
	bool searchHelper(size_t, const Node*, const String&, size_t&) const;

	void init(Node*);
	void copy(Node*, Node*);
	void destroy(Node*&);

	size_t m_size;
};

#endif // !_TRIE_HEADER_INCLUDED_
