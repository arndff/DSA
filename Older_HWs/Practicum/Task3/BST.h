#ifndef BST_HEADER_INCLUDED__
#define BST_HEADER_INCLUDED__

#include "Node.h"	
#include <vector>

class BST
{
public:
	BST();
	~BST();
	BST(const BST&);
	BST& operator=(const BST&);

public:
	void add(int);
	void remove(int);
	bool isMember(int) const;
	bool isEmpty() const;

	std::vector<int> generateNum() const;
	
private:
	void addHelper(Node*&, int);
	void removeHelper(Node*&, int);
	Node*& minNode(Node*&);
	void swapDelete(Node*&, Node*&);
	bool isMember(Node*, int) const;

	void generateNum(Node*, std::vector<int>&) const;

private:
	void copy(const BST&);
	void destroy();
	void copyHelper(Node*);
	void destroyHelper(Node*&);

private:
	Node* root;
};

inline BST::BST() 
{ 
	root = nullptr; 
}

inline BST::~BST() 
{ 
	destroy(); 
}

inline BST::BST(const BST& rhs)
	: root(nullptr)
{
	copy(rhs);
}

inline BST& BST::operator=(const BST& rhs)
{
	if (this != &rhs)
	{
		destroy();
		copy(rhs);
	}

	return *this;
}

inline void BST::add(int value)
{
	addHelper(root, value);
}

inline void BST::addHelper(Node*& n, int value)
{
	if (!n)
	{
		n = new Node(value);
		return;
	}

	if (value <= n->data)
		addHelper(n->left, value);
	else
		addHelper(n->right, value);
}

inline void BST::remove(int value)
{
	removeHelper(root, value);
}

inline void BST::removeHelper(Node*& n, int value)
{
	if (!n)
		return;

	if (n->data == value)
	{
		//if it's a leaf
		if (!n->left && !n->right)
		{
			delete n;
			n = NULL;
			return;
		}

		//if it doesn't have a left child
		if (!n->left)
		{
			Node* temp = n;
			n = n->right;

			temp->right = NULL;
			delete temp;
			temp = NULL;
			return;
		}

		//if it doesn't have a right child
		if (!n->right)
		{
			Node* temp = n;
			n = n->left;

			temp->left = NULL;
			delete temp;
			temp = NULL;
			return;
		}

		Node*& replacement = minNode(n->right);

		swapDelete(n, replacement);

		removeHelper(replacement, value);
	}

	if (value <= n->data)
		removeHelper(n->left, value);
	else
		removeHelper(n->right, value);
}

inline void BST::swapDelete(Node*& toDelete, Node*& New)
{
	int temp = toDelete->data;
	toDelete->data = New->data;
	New->data = temp;
}

inline Node*& BST::minNode(Node*& n)
{
	if (!n->left)
		return n;

	return minNode(n->left);
}

inline bool BST::isMember(int elem) const
{
	return isMember(root, elem);
}

inline bool BST::isMember(Node* n, int elem) const
{
	if (!n)
		return false;

	if (n->data == elem)
		return true;

	if (elem <= n->data)
		return isMember(n->left, elem);
	else
		return isMember(n->right, elem);
}

inline bool BST::isEmpty() const 
{ 
	return root == nullptr; 
}

inline std::vector<int> BST::generateNum() const
{
	std::vector<int> num;
	generateNum(root, num);
	return num;
}

inline void BST::generateNum(Node* n, std::vector<int>& num) const
{
	if (!n)
		return;

	generateNum(n->right, num);

	num.push_back(n->data);

	generateNum(n->left, num);
}

inline void BST::copy(const BST& rhs)
{
	copyHelper(rhs.root);
}

inline void BST::copyHelper(Node* n)
{
	if (!n)
		return;

	add(n->data);

	if (n->left)
		copyHelper(n->left);
	if (n->right)
		copyHelper(n->right);
}

inline void BST::destroy()
{
	destroyHelper(root);
}

inline void BST::destroyHelper(Node*& n)
{
	if (!n)
		return;

	destroyHelper(n->left);
	destroyHelper(n->right);

	delete n;
}

#endif //BST_HEADER_INCLUDED__