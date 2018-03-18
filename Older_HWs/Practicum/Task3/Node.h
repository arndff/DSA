#ifndef NODE_HEADER_INCLUDED__
#define NODE_HEADER_INCLUDED__

struct Node
{
	Node(int data, Node* _left = nullptr, Node* _right = nullptr)
		: data(_data)
		, left(_left)
		, right(_right)
	{}

	int data;
	Node* left;
	Node* right;
};

#endif //NODE_HEADER_INCLUDED__

#pragma once
