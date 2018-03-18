#include "Trie.h"

Trie::Trie()
{
	m_root = new Node;
	init(m_root);
	m_size = 0;
}

Trie::Trie(const Trie& rhs)
{
	m_root = new Node;
	init(m_root);
	copy(rhs.m_root, m_root);
	m_size = rhs.m_size;
}

Trie& Trie::operator=(const Trie& rhs)
{
	if (this != &rhs)
	{
		destroy(m_root);
		m_root = new Node;
		init(m_root);
		copy(rhs.m_root, m_root);
		m_size = rhs.m_size;
	}

	return *this;
}

Trie::~Trie()
{
	destroy(m_root);
}

//public functions
void Trie::insert(const String& word)
{
	size_t idx = 0;
	insert(m_root, word, idx);
	++m_size;
}

bool Trie::search(const String& word) const
{
	size_t idx = 0;

	return search(m_root, word, idx);
}

//some helper functions
void Trie::insert(Node*& root, const String& word, size_t& i)
{
	//when the whole word's processed, do this:
	if(i == word.getLen())
	{
		root->m_isEndOfWord = true;
		return;
	}

	//covering the case where word is a phrase
	if (word[i] == ' ')
	{
		size_t last = ALPHABET_SIZE - 1;
		insertHelper(last, root, word, i);
	}
	else
	{
		size_t idx = word[i] - (int)'a';
		insertHelper(idx, root, word, i);
	}
}

void Trie::insertHelper(size_t idx, Node*& root, const String& word, size_t& i)
{
	if (!root->m_children[idx])
	{
		root->m_children[idx] = new Node;
		init(root->m_children[idx]);
	}

	++i;
	insert(root->m_children[idx], word, i);
}

bool Trie::search(const Node* root, const String& word, size_t& i) const
{
	if(i == word.getLen())
	{
		(root->m_isEndOfWord) ? return true
		                      : return false;
	}

	//covering the case where word is a phrase
	if (word[i] == ' ')
	{
		size_t last = ALPHABET_SIZE - 1;
		searchHelper(last, root, word, i);
	}
	else
	{
		size_t idx = word[i] - (int)'a';
		searchHelper(idx, root, word, i);
	}
}

bool Trie::searchHelper(size_t idx, const Node* root, const String& word, size_t& i) const
{
	if (!root->m_children[idx])
	{
		return false;
	}
	else
	{
		++i;
		return search(root->m_children[idx], word, i, coeff);
	}
}

void Trie::init(Node* trieNode)
{
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		trieNode->m_children[i] = nullptr;
	}

	trieNode->m_coeff = 0;
	trieNode->m_isEndOfWord = false;
}

void Trie::copy(Node* from, Node* to)
{
	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		if (from->m_children[i])
		{
			to->m_children[i] = new Node;
			init(to->m_children[i]);

			to->m_children[i]->m_isEndOfWord = from->m_children[i]->m_isEndOfWord;

			copy(from->m_children[i], to->m_children[i]);
		}
	}
}

void Trie::destroy(Node*& root)
{
	if (!root) { return; }

	for (size_t i = 0; i < ALPHABET_SIZE; ++i)
	{
		if (root->m_children[i])
		{
			destroy(root->m_children[i]);
		}
	}

	delete root;
	root = nullptr;
}
