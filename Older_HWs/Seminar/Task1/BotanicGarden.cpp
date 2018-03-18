#include <iostream>
#include <fstream>
#include "BotanicGarden.h"

stack<Plant> readPlants(const char * fname)
{
	stack<Plant> plants;

	ifstream in(fname, ios::in);
	if (!in)
	{
		throw std::runtime_error("Can't open file for reading!\n");
	}

	int i;
	bool isLetter;

	while (!in.eof())
	{
		Plant buff;
		i = 0;
		isLetter = true;

		while (in && isLetter)
		{
			in >> buff.name[i];
			if (buff.name[i] >= '0' && buff.name[i] <= '9')
			{
				isLetter = false;
				buff.name[i] = '\0';
			}

			++i;
		}

		in.seekg(-1, ios::cur);

		in >> buff.min;
		in >> buff.max;

		plants.push(buff);
	}

	in.close();

	return plants;
}

//помощна функция, чрез която съм тествал подточка б)
stack<double> generateTemp()
{
	stack<double> temp;
	temp.push(10.2);
	temp.push(7.85);
	temp.push(15.32);
	temp.push(3.2);

	return temp;
}

queue<stack<Plant>> distributePlants(stack<Plant>& plants, stack<double>& temperatures)
{
	queue<stack<Plant>> distributedPlants;
	stack<Plant> tmp;
	double currT;

	while (!temperatures.empty())
	{
		stack<Plant> save;

		while (!plants.empty())
		{
			currT = temperatures.top();
			if (currT >= plants.top().min && currT < plants.top().max)
			{
				save.push(plants.top());
			}

			tmp.push(plants.top()); //след като сме проверили дали растението може да вирее при текущата температура,
							        //го push-ваме в нов стек, за да не го загубим
			plants.pop();
		}

		distributedPlants.push(save);

		//тук прехвърлям растенията от помощния стек в първоначалния стек с растения,
		//като на следващата итерация на външния while цикъл, проверявам отново
		//растенията едно по едно дали могат да виреят при текущата температура
		while (!tmp.empty())
		{
			plants.push(tmp.top());
			tmp.pop();
		}

		temperatures.pop();
	}

	return distributedPlants;
}

void avgTemp(stack<Plant>& plants, double temperature)
{
	ofstream os("botanic.bin", ios::binary | ios::trunc);
	if (!os)
	{
		throw std::runtime_error("Can't open the file for writing\n");
	}

	Plant buff;
	double currAvg;

	while (!plants.empty())
	{
		currAvg = (plants.top().min + plants.top().max) / 2;
		if (fabs(currAvg - temperature) <= 2)
		{
			buff = plants.top();
			os.write((char*)& buff, sizeof(buff));
		}

		plants.pop();
	}

	os.close();
}

void readPlantsTest()
{
	stack<Plant> plants = readPlants("plants.txt");

	//проверка дали данните от файла са записани правилно в стека
	size_t i = 1;
	while (!plants.empty())
	{
		cout << "Plant " << i << " name: " << plants.top().name << endl;
		cout << "Min temp: " << plants.top().min << endl;
		cout << "Max temp: " << plants.top().max << endl;

		cout << endl;

		++i;
		plants.pop();
	}
}

void distributePlantsTest()
{
	stack<Plant> plants = readPlants("plants.txt");
	stack<double> temperatures = generateTemp();
	queue< stack<Plant> > distributedPlants = distributePlants(plants, temperatures);

	//проверка дали данните са записани правилно в опашката
	stack<Plant> tmp;
	temperatures = generateTemp();

	while (!distributedPlants.empty())
	{
		tmp = distributedPlants.front();

		if (tmp.size() == 0)
		{
			cout << "There are no plants which can live in " << temperatures.top() << " degrees!\n\n";
		}
		else
		{
			cout << "The plants which can live in " << temperatures.top() << " degrees:\n";
			while (!tmp.empty())
			{
				cout << tmp.top().name << endl;
				tmp.pop();
			}

			cout << endl;
		}

		temperatures.pop();
		distributedPlants.pop();
	}
}

void avgTempTest()
{
	stack<Plant> plants = readPlants("plants.txt");
	double temperature;
	cout << "Enter a temperature: ";
	cin >> temperature;

	cout << endl;

	avgTemp(plants, temperature);

	ifstream is("botanic.bin", ios::binary);
	if (!is)
	{
		throw std::runtime_error("Can't open the file for reading!\n");
	}

	cout << "The plants which can live in " << temperature << " degrees: \n";

	Plant tmp;
	size_t i = 1;

	while (is.read((char*)& tmp, sizeof(tmp)))
	{
		cout << "Plant " << i << " name: " << tmp.name << endl;
		cout << "Min temp: " << tmp.min << endl;
		cout << "Max temp: " << tmp.max << endl;

		cout << endl;

		++i;
	}

	is.close();
}
