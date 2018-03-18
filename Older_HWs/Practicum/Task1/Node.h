#ifndef NODE_HEADER_INCLUDED__
#define NODE_HEADER_INCLUDED__

struct Node
{
	Node* left;
	Node* right;

	Node()
		: a(0)
		, b(0)
		, length(0)
		, left(nullptr)
		, right(nullptr)
	{
	}

	Node(int _a, int _b, Node* _left = nullptr, Node* _right = nullptr)
		: a(_a)
		, b(_b)
		, left(_left)
		, right(_right)
	{
		length = b - a + 1;
	}

	int a;
	int b;
	size_t length;
};

#endif //NODE_HEADER_INCLUDED__

