#ifndef INTERVAL_TREE_HEADER_INCLUDED__
#define INTERVAL_TREE_HEADER_INCLUDED__

#include "Node.h"	

class IntervalTree
{
public:
	IntervalTree();
	~IntervalTree();
	IntervalTree(const IntervalTree&);
	IntervalTree& operator=(const IntervalTree&);

public:
	void add(int, int);
	bool isEmpty() const { return root == nullptr; }
	
	struct Interval
	{
		int a;
		int b;
		Interval(int a, int b)
			: a(a)
			, b(b)
		{}
	};

	Interval findExtremum() const;

private:
	void addHelper(Node*& n, int, int);
	void findExtremum(Node*, int&, int&) const;

private:
	void copy(const IntervalTree&);
	void destroy();
	void copyHelper(Node*);
	void destroyHelper(Node*&);

private:
	Node* root;
};

inline IntervalTree::IntervalTree() 
{ 
	root = nullptr; 
}

inline IntervalTree::~IntervalTree() 
{ 
	destroy(); 
}

inline IntervalTree::IntervalTree(const IntervalTree& rhs) 
	: root(nullptr)
{
	copy(rhs);
}

inline IntervalTree& IntervalTree::operator=(const IntervalTree& rhs)
{
	if (this != &rhs)
	{
		destroy();
		copy(rhs);
	}

	return *this;
}

inline void IntervalTree::add(int a, int b)
{
	addHelper(root, a, b);
}

inline void IntervalTree::addHelper(Node*& n, int a, int b)
{
	if (!n)
	{
		n = new Node(a, b);
		return;
	}
	if ((b - a + 1) <= n->length)
		addHelper(n->left, a, b);
	else
		addHelper(n->right, a, b);
}

inline IntervalTree::Interval IntervalTree::findExtremum() const
{
	//these variables must have default values,
	//so we set them, respectively, with
	//the max and min value of an integer
	//int range : -2147483648 to 2147483647
	int min = 2147483647,
	    max = -2147483648;

	findExtremum(root, min, max);
	
	return Interval(min, max);
}

inline void IntervalTree::findExtremum(Node* n, int& min, int& max) const
{
	if (!n) 
		return;

	if (min >= n->a)
		min = n->a;
	if (max <= n->b)
		max = n->b;

	findExtremum(n->left, min, max);
	findExtremum(n->right, min, max);
}

inline void IntervalTree::copy(const IntervalTree& rhs)
{
	copyHelper(rhs.root);
}

inline void IntervalTree::copyHelper(Node* n)
{
	if (!n)
		return;

	add(n->a, n->b);

	if (n->left)
		copyHelper(n->left);
	if (n->right)
		copyHelper(n->right);
}

inline void IntervalTree::destroy()
{
	destroyHelper(root);
}

inline void IntervalTree::destroyHelper(Node*& n)
{
	if (!n)
		return;

	destroyHelper(n->left);
	destroyHelper(n->right);

	delete n;
}

#endif //INTERVAL_TREE_HEADER_INCLUDED__
