#ifndef _ELEVATOR_HEADER_INCLUDED_
#define _ELEVATOR_HEADER_INCLUDED_

#include <fstream>
#include "Queue.h"
#include "Vector.h"

class Elevator
{
public:
	Elevator(const char *);
	void processQueries();

private:
	Elevator(const Elevator&) = delete;
	Elevator& operator=(const Elevator&) = delete;

	struct Query
	{
		Query()
			: m_floor(-1)
			, m_time(-1)
		{}

		Query(size_t floor, size_t time)
			: m_floor(floor)
			, m_time(time)
		{}

		//friend std::ostream& operator<<(std::ostream&, const Query&);

		bool operator==(const Query& rhs) const { return m_floor == rhs.m_floor && m_time == rhs.m_time; }
		bool operator!=(const Query& rhs) const { return !(*this == rhs); }

		size_t m_floor;
		size_t m_time;
	};


	void getCurrQuery(Query&);
	bool notDone(const Query&);
	
	void processQueriesHelper(const Query&, size_t, size_t, const char*);
	size_t formula(size_t, size_t, size_t, const char*) const;
	void processFloor(Queue<Query>&, size_t, const char*, bool);
	void printDoneQuery(size_t, size_t, const char *) const;

	void removeDoneQs();

	void extractQueries(std::ifstream&);
	size_t getNum(std::ifstream&) const;
	bool isLetter(char c) const;

private:
	static const size_t SPEED = 5; //5s -> 1 floor

	size_t m_floorsCnt; //N = floors count
	size_t m_queriesCnt; //K = queries count
	Queue<Query> m_queries;
	Vector<Queue<Query>> m_arr;
	Vector<Query> m_passed;
};

#endif // !_ELEVATOR_HEADER_INCLUDED_