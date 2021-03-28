#include <iostream>
#include <fstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Dictionary/Dictionary.h"

SCENARIO("OpenFile")
{
	std::fstream file;
	REQUIRE(OpenFile(file, "test_dict.txt"));
}

SCENARIO("Init Dictionary")
{
	std::fstream file;
	REQUIRE(OpenFile(file, "test_dict.txt"));

	map<string, string> dictionary;
	InitDictionary(file, dictionary);
	REQUIRE(dictionary.size() == 1);
	REQUIRE(dictionary.begin()->first == "home");
	REQUIRE(dictionary.begin()->second == "дом");
}

SCENARIO("Init Dictionary")
{
	std::fstream file;
	REQUIRE(OpenFile(file, "test_dict.txt"));

	map<string, string> dictionary;
	InitDictionary(file, dictionary);
	REQUIRE(dictionary.size() == 1);
	REQUIRE(dictionary.begin()->first == "home");
	REQUIRE(dictionary.begin()->second == "дом");
}

SCENARIO("Working with dictionary")
{
	std::fstream file;
	REQUIRE(OpenFile(file, "test_dict.txt"));

	map<string, string> dictionary;
	InitDictionary(file, dictionary);
	REQUIRE(dictionary.size() == 1);
	REQUIRE(dictionary.begin()->first == "home");
	REQUIRE(dictionary.begin()->second == "дом");
	WorkingDictionary()
}