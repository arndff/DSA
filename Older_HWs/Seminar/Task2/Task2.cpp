#include <iostream>
#include <cassert>
#include "Task2.h"

bool isNegative(double num)
{
	return num < 0;
}

bool isPositive(double num)
{
	return num > 0;
}

double findSum(queue<double>& q, fPtr pred)
{
	double sum = 0;
	while (!q.empty())
	{
		if (pred(q.front()))
		{
			sum += q.front();
		}

		q.pop();
	}
	return sum;
}

double solution(list< queue<double> >& l)
{
	double sum1 = 0, sum2 = 0, res = 0;

	//std::list< queue<double> >::const_iterator
	for (auto it = l.begin(); it != l.end(); ++it)
	{
		sum1 += findSum(*it, isPositive);
		sum2 = 0;

		auto tmp = it;

		for (auto it2 = ++tmp; it2 != l.end(); ++it2)
		{
			sum2 += findSum(*it2, isNegative);
		}

		if (sum1 == fabs(sum2))
		{
			res = sum1;
		}
	}

	if (res != 0)
	{
		cout << "The answer is: " << res << endl;
		return res;
	}
	else
	{
		cout << "No solution!\n";
		return res;
	}
}

void input()
{
	size_t n;
	do
	{
		cout << "Enter queues count: ";
		cin >> n;
	} while (n < 2);

	list< queue<double> > l;
	size_t cnt;
	double elem;

	for (size_t i = 0; i < n; ++i)
	{
		queue<double> curr;
		do
		{
			cout << "Elements count for Queue " << i + 1 << ": ";
			cin >> cnt;
		} while (cnt < 1);

		while (cnt != 0)
		{
			cout << "Enter a fraction: ";
			cin >> elem;

			curr.push(elem);

			--cnt;
		}

		l.push_back(curr);
	}

	solution(l);
}

void test()
{
	queue<double> q1;
	q1.push(5.2);
	q1.push(-3.1);
	q1.push(2.4);

	queue<double> q2;
	q2.push(1.3);
	q2.push(-4.2);

	queue<double> q3;
	q3.push(-3.4);

	list< queue<double> > l;
	l.push_back(q1);
	l.push_back(q2);
	l.push_back(q3);

	double answer = solution(l);
	assert(answer == 7.6);
}
