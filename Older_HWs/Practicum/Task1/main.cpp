#include <iostream>
#include "IntervalTree.h"

using namespace std;

void test()
{
	size_t n;
	cout << "Enter the nodes count: ";
	cin >> n;

	IntervalTree tree;
	
	int left = 0, right = 0;

	for (size_t i = 0; i < n; ++i)
	{
		do
		{
			cout << "Enter a[" << i << "]: ";
			cin >> left;
			cout << "Enter b[" << i << "]: ";
			cin >> right;
		} while (left > right);

		tree.add(left, right);
	}

	cout << "The interval which contains all tree intervals is: "
		 << "["
		 << tree.findExtremum().a
		 << "; "
		 << tree.findExtremum().b
		 << "]"
		 << endl;
}

int main()
{
	test();

	return 0;
}