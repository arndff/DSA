#include "SortingAlgorithms.h"

template <class T>
bool binarySearch(T* arr, size_t left, size_t right, const T& elem)
{
	if (left < right)
	{
		size_t middle = left + (right - left) / 2;

		if (elem < arr[middle])
		{
			return binarySearch(arr, left, middle - 1, elem);
		}
		else if (elem > arr[middle])
		{
			return binarySearch(arr, middle + 1, right, elem);
		}
		else
		{
			return true;
		}
	}

	return false;
}

template <class T>
void contains(T* arr, size_t size, const T& elem)
{
	std::cout << "\nDoes array contain " << elem << "?\n";
	(binarySearch(arr, 0, size - 1, elem)) ? std::cout << "Yes\n"
									  	   : std::cout << "No\n";
}

void test()
{
	int arr[] = { 5,13,9,14,20,3,2,10 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	sortArr(arr, size);
	print(arr, size);

	contains(arr, size, 13);
	contains(arr, size, 42);
}

int main()
{
	test();

	return 0;
}