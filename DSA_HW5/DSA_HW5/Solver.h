#ifndef SOLVER_HEADER_INCLUDED__
#define SOLVER_HEADER_INCLUDED__

#include "HashTable.h"

#include <iostream>
#include <string>
#include <fstream>

size_t calculateSize(const std::string& path);
void initTable(const std::string& path, HashTable<int, int>& table);

void processSingleFile(const std::string& path, HashTable<int, int>& table, size_t);
void processFiles(std::string* paths, size_t size, HashTable<int, int>& table);

void findIntersection(size_t size, const HashTable<int, int>& table);
void printIntersection();

size_t intHash(const int&, size_t);

void solution();

#endif // !SOLVER_HEADER_INCLUDED__
