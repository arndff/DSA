#ifndef TASK3_HEADER_INCLUDED__
#define TASK3_HEADER_INCLUDED__

#include "BST.h"

using namespace std;

void print(const vector<int>&);

vector<int> refill(const vector<int>&, size_t);

void sumHelper(const vector<int>&, const vector<int>&);
void sum(const vector<int>&, const vector<int>&);

void calculate(const BST&, const BST&);

void test();

#endif // !TASK3_HEADER_INCLUDED__
