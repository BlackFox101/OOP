#include <iostream>
#include <string>
#include "FindMaxEx.h"

using namespace std;

struct Sportsman
{
	string FIO;
	int height;
	int weight;
};

int main()
{
	vector<Sportsman> sportsmans;

	sportsmans.push_back({ "Ivan",		10, 60 });
	sportsmans.push_back({ "Dmitriy",	20, 50 });
	sportsmans.push_back({ "Alexey",	30, 40 });
	sportsmans.push_back({ "Oleg",		40, 30 });
	sportsmans.push_back({ "Andrey",	50, 20 });
	sportsmans.push_back({ "kolya",		60, 10 });

	Sportsman maxValue;

	FindMax(sportsmans, maxValue, [](Sportsman a, Sportsman b) { return a.height < b.height; });
	cout << "The highest sportsman '" << maxValue.FIO << "' with a height of: " << maxValue.height << endl;

	FindMax(sportsmans, maxValue, [](Sportsman a, Sportsman b) { return a.weight < b.weight; });
	cout << "The heaviest sportsman '" << maxValue.FIO << "' with a weight of: " << maxValue.weight << endl;
}