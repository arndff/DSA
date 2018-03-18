#include <iostream>
#include "BST.h"

using namespace std;

void test()
{
	BST tree;
	tree.add(5);
	tree.add(2);
	tree.add(8);
	tree.add(1);
	tree.add(4);
	tree.add(6);

	cout << "Printing the tree using in-order traversal: ";
	tree.print();
	cout << "\n\n";

	tree.swapAllNodes();

	cout << "Priting the modified tree: ";
	tree.print();
	cout << endl;
}

int main()
{
	test();

	return 0;
}