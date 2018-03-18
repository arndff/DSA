#include "Elevator.h"

/*
std::ostream &operator<<(std::ostream& out, const Elevator::Query& q)
{
	out << q.m_floor << " " << q.m_time << "\n";
	return out;
}
*/

Elevator::Elevator(const char* path)
{
	if (!path)
	{
		throw std::runtime_error("Invalid path has been passed.\n");
	}
	else
	{
		std::ifstream in(path);
		if (!in) 
		{ 
			throw std::runtime_error("Can't open the file for reading.\n");
		}

		extractQueries(in);

		in.close();
 	}
 }

void Elevator::processQueries()
{
	size_t currFloor = 1;
	Query currQuery;
	size_t currTime = m_queries.getFront().m_time;
	const size_t DIR_LEN = 4;

	while (!m_queries.isEmpty())
	{
		getCurrQuery(currQuery); //get-and-remove (actually)

		if (notDone(currQuery))
		{
			char dir[DIR_LEN + 1];
			
			if(( (int)currQuery.m_floor - (int)currFloor ) > 0)
			{
				strcpy(dir, "up");
			}
			else
			{
				strcpy(dir, "down");
			}

			currTime += fabs(((int)currQuery.m_floor - (int)currFloor)) * SPEED;
			processQueriesHelper(currQuery, currTime, currFloor, dir);

			printDoneQuery(currTime, currQuery.m_floor, dir);

			currFloor = currQuery.m_floor;

			removeDoneQs();
			m_passed.destroy(); //remove passed queries; don't need them on next iteration
		}
	}
}

void Elevator::getCurrQuery(Query& currQuery)
{
	currQuery = m_queries.getFront();
	m_queries.dequeue();
}

//check whether currQuery has to be processed
bool Elevator::notDone(const Query& currQuery)
{
	bool notProcessed = false;
	Queue<Query> tmp;

	//if we find currQuery, won't add it to tmp
	while (!m_arr[currQuery.m_floor - 1].isEmpty())
	{
		Query x = m_arr[currQuery.m_floor - 1].getFront();
		m_arr[currQuery.m_floor - 1].dequeue();
		if (x != currQuery)
		{
			tmp.enqueue(x);
		}
		else
		{
			notProcessed = true;
		}
	}

	//remove all the queries but without currQuery
	m_arr[currQuery.m_floor - 1] = tmp;

	if (notProcessed)
	{
		return true; //then we have to process this query
	}
	else
	{
		return false;
	}
}

void Elevator::processQueriesHelper(const Query& currQuery, size_t currTime, size_t currFloor, const char* dir)
{
	bool sameFloor = false; //a var which indicates whether the loop reached the same floor
	                        //if yes, then just don't print passable queries there
	                        //'cause they'll be printed @processQuery function

	if (strcmp(dir, "up") == 0)
	{
		for (size_t i = currFloor - 1; i < currQuery.m_floor; ++i)
		{
			size_t estimatedTime = formula(currTime, currQuery.m_floor, i + 1, dir); //calc when the elevator will reach floor i+1
			sameFloor = (i + 1 == currQuery.m_floor); //last iteration
			processFloor(m_arr[i], estimatedTime, dir, sameFloor); //process queries from floor i
		}
	}
	else
	{
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for (int i = currFloor - 1; i >= currQuery.m_floor; --i)
		{
			size_t estimatedTime = formula(currTime, currQuery.m_floor, i, dir); //calc when the elevator will reach floor i
			sameFloor = (i == currQuery.m_floor); //last iteration
			processFloor(m_arr[i - 1], estimatedTime, dir, sameFloor); //process queries from floor i-1
		}
	}
}

//res = 21 - (5-4)*5 = 21 - 5 = 16 which means that the elevator will reach 4th floor @16sec
//the direction matters; example below works for "up"
//when dir = "down", change target & curr order
size_t Elevator::formula(size_t reach, size_t target, size_t curr, const char* dir) const
{
	if (strcmp(dir, "up") == 0)
	{
		return reach - (target - curr)*SPEED;
	}
	else
	{
		return reach - (curr - target)*SPEED;
	}
}

void Elevator::processFloor(Queue<Query>& q, size_t estimatedTime, const char* dir, bool sameFloor)
{
	bool printed = false;

	while (!q.isEmpty())
	{
		Query x = q.getFront();
		if (x.m_time <= estimatedTime)
		{
			if (!sameFloor && !printed) 
			{
				printDoneQuery(estimatedTime, q.getFront().m_floor, dir);
				printed = true; 
			}

			q.dequeue();
			m_passed.push_back(x); //save passed query
		}
		else
		{
			return;
		}
	}
}

void Elevator::printDoneQuery(size_t time, size_t floor, const char* dir) const
{
	std::cout << time << " " << floor << " " << dir << "\n";
}

//remove already passed queries from m_queries
void Elevator::removeDoneQs()
{
	Queue<Query> tmp;
	
	while (!m_queries.isEmpty())
	{
		Query x = m_queries.getFront();
		m_queries.dequeue();

		if (!m_passed.contains(x))
		{
			tmp.enqueue(x);
		}
	}

	m_queries = tmp;
}

///read queries from txt file
//save all queries to m_queries
//and add them to m_arr
void Elevator::extractQueries(std::ifstream& in)
{
	//read N, K
	m_floorsCnt = getNum(in);
	m_queriesCnt = getNum(in);

	//init m_arr
	for (size_t i = 0; i < m_floorsCnt; ++i)
	{
		Queue<Query> q;
		m_arr.push_back(q);
	}

	while (!in.eof())
	{
		while (isLetter(in.peek())) { in.get(); } //skip type and direction 'cause we don't need them

		if (in.eof()) { break; } //we need this check, if the file ends with a newline

		size_t floor = getNum(in);
		size_t time = getNum(in);

		Query q(floor, time);
		m_queries.enqueue(q);
		m_arr[floor - 1].enqueue(q);
	}
}

bool Elevator::isLetter(char c) const
{
	return (c >= 'a' && c <= 'z') || c == ' ';
}

size_t Elevator::getNum(std::ifstream& in) const
{
	size_t res;
	in >> res;
	in.get();
	return res;
}
