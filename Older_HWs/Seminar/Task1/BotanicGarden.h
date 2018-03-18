#ifndef BOTANIC_GARDEN_HEADER_INCLUDED__
#define BOTANIC_GARDEN_HEADER_INCLUDED__

#include <stack>
#include <queue>

using namespace std;

struct Plant
{
	char name[20];
	double min;
	double max;

	Plant()
		: name("")
		, min(0)
		, max(0)
	{}

	Plant(char* _name, double _min, double _max)
		: min(_min)
		, max(_max)
	{
		strcpy(name, _name);
	}
};

stack<Plant> readPlants(const char *);
stack<double> generateTemp();
queue< stack<Plant> > distributePlants(stack<Plant>&, stack<double>&);
void avgTemp(stack<Plant>&, double);

void readPlantsTest();
void distributePlantsTest();
void avgTempTest();

#endif // !BOTANIC_GARDEN_HEADER_INCLUDED__
