#include "Solver.h"

size_t calculateSize(const std::string& path)
{
	std::ifstream ifs(path, std::ios::binary);
	if (!ifs) 
	{ 
		std::runtime_error("Problem while opening the first file.\n"); 
	}

	ifs.seekg(0, std::ios::end);
	size_t cnt = ifs.tellg() / sizeof(int);
	ifs.seekg(0, std::ios::beg);

	ifs.close();

	return cnt;
}

void initTable(const std::string& path, HashTable<int, int>& table)
{
	std::ifstream ifs(path, std::ios::binary);
	if (!ifs) 
	{ 
		throw std::runtime_error("Problem with some of the files.\n"); 
	}	

	int num = 0;
	const int VALUE = 0; //stands for first file

	while (ifs.read((char*)& num, sizeof(num)))
	{
		if (!table.search(num))
		{
			table.insert(num, VALUE);
		}
	}
}

void processSingleFile(const std::string& path, HashTable<int, int>& table, size_t idx)
{
	std::ifstream ifs(path, std::ios::binary);
	if (!ifs)
	{ 
		throw std::runtime_error("Problem with some of the files.\n");
	}

	int num = 0;

	while (ifs.read((char*)& num, sizeof(num)))
	{
		if (table.search(num) && table[num] != idx)
		{
			table.insert(num, idx);
		}
	}
}

void processFiles(std::string* paths, size_t size, HashTable<int, int>& table)
{
	for (size_t i = 0; i < size; ++i)
	{
		processSingleFile(paths[i], table, i+1);
	}
}

void findIntersection(size_t size, const HashTable<int, int>& table)
{
	std::ofstream ofs("result.bin", std::ios::binary | std::ios::trunc);
	if (!ofs) 
	{ 
		throw std::runtime_error("Problem with the result.bin file.\n"); 
	}

	//iterate through all hash table's pairs
	//if a pair's value is equal to the count of files (size)
	//therefore, its key is part of the intersection,
	//so save that key @ results.bin

	table.intersection(ofs, size);

	ofs.close();
}

void printIntersection()
{
	std::ifstream ifs("result.bin", std::ios::binary);
	if (!ifs) 
	{ 
		throw std::runtime_error("Problem with the result.bin file.\n");
	}

	int num = 0;
	while (ifs.read((char*)& num, sizeof(int)))
	{
		std::cout << num << " ";
	}

	std::cout << "\n";

	ifs.close();
}

size_t intHash(const int& num, size_t size)
{
	return num % size;
}

void input(std::string* paths, size_t& n)
{
	do
	{
		std::cout << "Enter files count: ";
		std::cin >> n;
	} while (n < 1);

	paths = new std::string[n];

	std::cin.ignore();

	for (size_t i = 0; i < n; ++i)
	{
		std::cout << "Enter path " << i + 1 << ": ";
		std::getline(std::cin, paths[i]);
	}
}

void solution()
{
	//size_t n = 0;
	//std::string * paths;
	
	//input(paths, n);

	size_t n = 4;
	std::string paths[4] = { "f1.bin",
				 "f2.bin",
				 "f3.bin",
				 "f4.bin" };

	//solution goes here:

	size_t hashTableSize = calculateSize(paths[0]);
	HashTable<int, int> table(intHash, hashTableSize);

	initTable(paths[0], table); //init the HT with first file's content
	processFiles(paths + 1, n - 1, table); //passing all the paths without the first one
	findIntersection(n - 1, table);
	printIntersection();
}
