#include <iostream>
#include <fstream>
#include <Windows.h>
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
	REQUIRE(dictionary.begin()->second == "���");
}

SCENARIO("SaveWorld")
{
	std::istringstream input("������");
	map<string, string> dictionary;
	SaveWord(dictionary, "Hello", input);
	REQUIRE(dictionary.size() == 1);
	REQUIRE(dictionary.begin()->first == "Hello");
	REQUIRE(dictionary.begin()->second == "������");
}

SCENARIO("TranslateWord")
{
	std::fstream file;
	REQUIRE(OpenFile(file, "test_dict.txt"));

	map<string, string> dictionary;
	InitDictionary(file, dictionary);
	REQUIRE(dictionary.size() == 1);
	REQUIRE(dictionary.begin()->first == "home");
	REQUIRE(dictionary.begin()->second == "���");

	std::ostringstream output("");
	TranslateWord("home", dictionary, output);
	REQUIRE(output.str() == "���\n");
}

SCENARIO("Working with dictionary")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::fstream file;
	REQUIRE(OpenFile(file, "test_dict.txt"));

	map<string, string> dictionary;
	InitDictionary(file, dictionary);
	REQUIRE(dictionary.size() == 1);
	REQUIRE(dictionary.begin()->first == "home");
	REQUIRE(dictionary.begin()->second == "���");

	//WorkingDictionary(file, dictionary);
}