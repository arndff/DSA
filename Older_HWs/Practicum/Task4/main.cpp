#include <iostream>
#include <queue>

using std::cout;
using std::cin;
using std::queue;

bool check(int i, int c) 
{ 
	return i == c; 
}
	
int solution(int num, int idx)
{
	queue<int> q;
	
	q.push(num);
	int curr = q.front();
	size_t cnt = 0;

	while (true)
	{
		q.push(curr + 1); 
		++cnt;
		if (check(idx, cnt)) 
		{ 
			return q.back(); 
		}

		q.push(2 * curr); 
		++cnt;
		if (check(idx, cnt)) 
		{ 
			return q.back(); 
		}
		
		q.pop();
		curr = q.front();
	}
}

void test()
{
	int N = 0,
		p = 0;

	do
	{
		cout << "Enter N: ";
		cin >> N;
		cout << "Enter p: ";
		cin >> p;
	} while (p < 0);

	if (p == 0)
	{
		cout << "The number with index 0 is: "
			 << N
			 << "\n";
	}
	else
	{
		cout << "The number with index "
			 << p
			 << " is: "
			 << solution(N, p)
			 << "\n";
	}
}

int main()
{
	test();

	return 0;
}