#ifndef TASK2_HEADER_INCLUDED__
#define TASK2_HEADER_INCLUDED__

#include <list>
#include <queue>
#include <string>

using namespace std;

typedef bool(*fPtr)(double);

bool isNegative(double);
bool isPositive(double);

double findSum(queue<double>& q, fPtr pred);
double solution(list< queue<double> >& l);

void input();
void test();

#endif // !TASK2_HEADER_INCLUDED__
