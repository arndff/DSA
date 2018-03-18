#include <iostream>
#include <algorithm>
#include "Task3.h"

void print(const vector<int>& v)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i];
	}
}

//a function which takes as arguments
//the smaller vector and the size of the bigger one
//an example of function's purpose:
//vec:   123, size: 5
//res: 00123
vector<int> refill(const vector<int>& vec, size_t size)
{
	vector<int> result(size);
	size_t len = size - vec.size();

	for (size_t i = 0; i < len; ++i)
	{
		result[i] = 0;
	}

	for (size_t i = 0; i < vec.size(); ++i)
	{
		result[len++] = vec[i];
	}

	return result;
}

void sumHelper(const vector<int>& num1, const vector<int>& num2)
{
	vector<int> _num1 = refill(num1, num2.size());

	//we are sure that num1.size() <= num2.size() (see void sum(...) function)
	//so we want a new vector with num2.size() + 1
	//example:
	//num1:    999 (size 3)
	//num2:  99999 (size 5)
	// res: 100998 (size 6)
	vector<int> result(num2.size() + 1);

	int size = num2.size();
	int tmp = 0;

	for (int i = size - 1; i >= 0; --i)
	{
		tmp += _num1[i] + num2[i];
		if (tmp / 10 == 0)
		{
			result[size--] = tmp;
			tmp = 0;
		}
		else
		{
			result[size--] = tmp % 10;
			tmp /= 10;
		}
	}

	result[0] = tmp;

	if (result[0] != 0)
	{
		print(num1);
		cout << " + ";
		print(num2);
		cout << " = ";
		print(result);
		cout << endl;
	}
	else
	{
		print(num1);
		cout << " + ";
		print(num2);
		cout << " = ";
		for (size_t i = 1; i < result.size(); ++i)
		{
			cout << result[i];
		}

		cout << "\n\n";
	}
}

void sum(const vector<int>& v1, const vector<int>& v2)
{
	if (v1.size() <= v2.size())
	{
		sumHelper(v1, v2);
	}
	else
	{
		sumHelper(v2, v1);
	}
}

void calculate(const BST& tree, const BST& tree2)
{
	vector<int> num1 = tree.generateNum();
	vector<int> num2 = tree2.generateNum();

	sum(num1, num2);
}

void test()
{
	///Example 1
	//a tree which represents our first number
	BST tree;
	tree.add(5);
	tree.add(3);
	tree.add(7);
	tree.add(6);
	tree.add(9);

	//a tree which represents our second number
	BST tree2;
	tree2.add(7);
	tree2.add(5);
	tree2.add(9);
	tree2.add(8);

	calculate(tree, tree2);

	///Example 2
	BST tree3;
	tree3.add(9);
	tree3.add(9);
	tree3.add(9);
	tree3.add(9);

	BST tree4;
	tree4.add(1);
	
	calculate(tree3, tree4);
}