#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../FindMaxEx/FindMaxEx.h"

using namespace std;

SCENARIO(" INT ")
{
	WHEN("Empty vector")
	{
		vector<int> empty;
		int maxValue;
		REQUIRE(FindMax(empty, maxValue, [](int a, int b) { return a < b; }) == false);
	}

	WHEN("Vector of integers")
	{
		vector<int> numbers = { 1,2,3,4,5 };
		int maxValue;
		REQUIRE(FindMax(numbers, maxValue, [](int a, int b) { return a < b; }));
		CHECK(maxValue == 5);
	}
}

SCENARIO("Double")
{
	WHEN("Empty vector")
	{
		vector<double> empty;
		double maxValue;
		REQUIRE(FindMax(empty, maxValue, [](double a, double b) { return a < b; }) == false);
	}

	WHEN("Vector of integers")
	{
		vector<double> numbers = { 1.1, 1.2 ,1.3, 1.4, 1.5 };
		double maxValue;
		REQUIRE(FindMax(numbers, maxValue, [](double a, double b) { return a < b; }));
		CHECK(maxValue == 1.5);
	}
}

SCENARIO("String")
{
	WHEN("Empty vector")
	{
		vector<string> empty;
		string maxValue;
		REQUIRE(FindMax(empty, maxValue, [](string a, string b) { return a < b; }) == false);
	}

	WHEN("Vector of integers")
	{
		vector<string> strings = { "abc", "abcd" , "abcde" };
		string maxValue;
		REQUIRE(FindMax(strings, maxValue, [](string a, string b) { return a < b; }));
		CHECK(maxValue == "abcde");
	}
}

SCENARIO("Sportsmans")
{
	struct Sportsman
	{
		string FIO;
		int height;
		int weight;
	};
	vector<Sportsman> sportsmans;

	sportsmans.push_back({ "Ivan",		10, 60 });
	sportsmans.push_back({ "Dmitriy",	20, 50 });
	sportsmans.push_back({ "Alexey",	30, 40 });
	sportsmans.push_back({ "Oleg",		40, 30 });
	sportsmans.push_back({ "Andrey",	50, 20 });
	sportsmans.push_back({ "kolya",		60, 10 });
	Sportsman maxValue;

	REQUIRE(FindMax(sportsmans, maxValue, [](Sportsman a, Sportsman b) { return a.height < b.height; }));
	CHECK(maxValue.height == maxValue.height);

	REQUIRE(FindMax(sportsmans, maxValue, [](Sportsman a, Sportsman b) { return a.weight < b.weight; }));
	CHECK(maxValue.weight == maxValue.weight);
}