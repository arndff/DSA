#ifndef SORTING_ALGORITHMS_HEADER_INCLUDED__
#define SORTING_ALGORITHMS_HEADER_INCLUDED__

#include <iostream>
#include <algorithm>

template <class T>
void bubbleSort(T* arr, size_t size)
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		//last "size-i-1" elements are already sorted,
		//so there's no point to make comparisons there
		for (size_t j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}

template <class T>
void selectionSort(T* arr, size_t size)
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		int min = i;

		//found the idx of min element
		//swap with curr min if needed
		for (size_t j = i + 1; j < size; ++j)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}

		std::swap(arr[i], arr[min]);
	}
}

template <class T>
void insertionSort(T* arr, size_t size)
{
	for (size_t i = 1; i < size; ++i)
	{
		size_t j = i;
		//going backwards until we find
		//curr element's place into the arr
		while (j > 0 && arr[j] < arr[j - 1])
		{
			std::swap(arr[j], arr[j - 1]);
			--j;
		}
	}
}


void countingSort(int* arr, size_t size)
{
	int maxElem = arr[0];

	for (size_t i = 1; i < size; ++i)
	{
		if (arr[i] > maxElem)
		{
			maxElem = arr[i];
		}
	}

	//make an array with size maxElem + 1
	//'cause we want to include the maxElem too
	size_t countsSize = maxElem + 1;
	int* counts = new int[countsSize];

	for (size_t i = 0; i < countsSize; ++i)
	{
		counts[i] = 0;
	}

	//keys from arr are indices in counts array
	//so we count each key's occurences
	for (size_t i = 0; i < size; ++i)
	{
		counts[arr[i]]++;
	}

	//sorting's done here:
	size_t pos = 0;

	for (size_t i = 0; i < countsSize; ++i)
	{
		while (counts[i] > 0)
		{
			arr[pos++] = i;
			--counts[i];
		}
	}

	delete[] counts;
}


template <class T>
void merge(T *arr, int left, int right) {

	//additional memory for merging
	T* copy = new int[left + right];

	// indexes of the first half , second and copied
	int leftIndex = 0, rightIndex = left, copyIndex = 0;

	//iterating both left and right parts
	//in each step we
	//take the smaller element form each part
	//and copy it in 'copy' array
	//in order to have sorted sequence in copy array at the end
	while (leftIndex < left && rightIndex < left + right)
	{
		if (arr[leftIndex] < arr[rightIndex])
		{
			copy[copyIndex++] = arr[leftIndex++];
		}
		else
		{
			copy[copyIndex++] = arr[rightIndex++];
		}
	}

	//we have elements left in the first half
	//just copy them in the sorted array 'copy'
	while (leftIndex < left)
	{
		copy[copyIndex++] = arr[leftIndex++];
	}

	while (rightIndex < left + right)
	{
		copy[copyIndex++] = arr[rightIndex++];
	}

	//copy the memory back into the given array
	memcpy(arr, copy, sizeof(int)*(left + right));

	delete[] copy;
};

template <class T>
void mergeSort(T* arr, int size, T* buffer)
{
	if (size == 1)
	{
		return;
	}

	if (size == 2)
	{
		if (arr[0] > arr[1])
		{
			std::swap(arr[0], arr[1]);
		}

		return;
	}

	size_t mid = size / 2;

	//dividing in two parts
	mergeSort(arr, mid, buffer);
	mergeSort(arr + mid, size - mid, buffer);

	//merging the two sorted parts into one array
	merge(arr, mid, size - mid);

}

template <class T>
void mergeSort(T* arr, size_t size)
{
	T* buffer = new int[size];
	mergeSort(arr, size, buffer);

	delete[] buffer;
}


template <class T>
void quickSort(T* arr, int size)
{
	if (size == 1)
	{
		return;
	}

	if (size == 2)
	{
		if (arr[0] > arr[1])
		{
			std::swap(arr[0], arr[1]);
		}

		return;
	}

	int left = 0, right = size - 1;
	int pivot = std::max(std::min(arr[size / 2], arr[size - 1]),
		std::min(std::max(arr[size / 2], arr[size - 1]), arr[0]));

	while (left <= right)
	{
		//finding the first available 
		//element in the left half
		while (arr[left] < pivot)
		{
			++left;
		}

		//in the right half
		while (arr[right] > pivot)
		{
			--right;
		}

		//swap them
		if (left <= right)
		{
			std::swap(arr[left], arr[right]);
			++left;
			--right;
		}

	}

	//sorting LEFT half
	if (right > 0)
	{
		quickSort(arr, right + 1);
	}

	//sorting RIGHT half
	if (left < size)
	{
		quickSort(arr + left, size - left);
	}
}


template <class T>
void print(T* arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << arr[i] << " ";
	}

	std::cout << "\n";
}

template <class T>
void sortArr(T* arr, size_t size)
{
	size_t choice;
	while (true)
	{
		std::cout << "1. Bubble Sort\n";
		std::cout << "2. Selection Sort\n";
		std::cout << "3. Insertion Sort\n";
		std::cout << "4. Counting Sort\n";
		std::cout << "5. Merge Sort\n";
		std::cout << "6. Quick Sort\n\n";
		std::cout << "Choose a sorting algorithm: ";

		do
		{
			std::cin >> choice;
		} while (choice < 1 || choice > 6);

		switch (choice)
		{
		case 1:
			bubbleSort(arr, size);
			return;
		case 2:
			selectionSort(arr, size);
			return;
		case 3:
			insertionSort(arr, size);
			return;
		case 4:
			countingSort(arr, size);
			return;
		case 5:
			mergeSort(arr, size);
			return;
		case 6:
			quickSort(arr, size);
			return;
		}
	}
}

#endif // !SORTING_ALGORITHMS_HEADER_INCLUDED__
