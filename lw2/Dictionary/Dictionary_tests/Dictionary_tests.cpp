#include <iostream>
#include <fstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Dictionary/Dictionary.h"

//SCENARIO("OpenFile")
//{
//	std::fstream file;
//	REQUIRE(OpenFile(file, "Dictionary.txt"));
//}

//SCENARIO(Init Dictionary)
//{
//	/*std::istringstream input("1 line");
//	THEN("output stream contains the line reversed")
//	{
//		ReverseLines(input, output);*/
//	std::istringstream input("home-дом");
//	map<string, string> dictionary;
//	REQUIRE(InitDictionary(input, dictionary));
//}