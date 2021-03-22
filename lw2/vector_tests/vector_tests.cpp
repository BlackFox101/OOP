#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../vector/vector.h"


SCENARIO("Read vector")
{
	//std::ostringstream output;
	WHEN("Some elements")
	{
		std::istringstream input("12.1 1.1 15.23");
		vector<float> numbers = ReadVector(input);
		REQUIRE(numbers.size() == 3);
		CHECK(input.eof());
		THEN("Checking values")
		{
			REQUIRE(numbers[0] == 12.1f);
			REQUIRE(numbers[1] == 1.1f);
			REQUIRE(numbers[2] == 15.23f);
		}
	}

	WHEN("Empty string")
	{
		std::istringstream input("");
		REQUIRE(ReadVector(input).size() == 0);
		CHECK(input.eof());
	}
}

SCENARIO("Find minimal value position in matrix")
{
	REQUIRE(FindMinValuePosition({ 1, 2, 3 }) == 0);
	REQUIRE(FindMinValuePosition({ 1, 1, 3 }) == 0);
	REQUIRE(FindMinValuePosition({ 1 }) == 0);
}

SCENARIO("Multiply vector elements")
{
	//std::ostringstream output;
	WHEN("Some elements")
	{
		vector<float> numbers = { 2, 2, 3 };
		MultiplyElementsVector(numbers, numbers[0]);
		REQUIRE(numbers.size() == 3);
		REQUIRE(numbers[0] == 4);
		REQUIRE(numbers[1] == 4);
		REQUIRE(numbers[2] == 6);
	}
}

SCENARIO("Output vector")
{
	std::ostringstream output;
	vector<float> numbers = { 2, 2, 3 };
	THEN("output stream is also empty")
	{
		OutputVector(output, numbers);
		CHECK(output.str() == "2\n2\n3\n");
	}
}

SCENARIO("Sort vector")
{
	vector<float> numbers = { 3, 2, 1 };
	SortVector(numbers);
	REQUIRE(numbers.size() == 3);
	REQUIRE(numbers[0] == 1);
	REQUIRE(numbers[1] == 2);
	REQUIRE(numbers[2] == 3);
}