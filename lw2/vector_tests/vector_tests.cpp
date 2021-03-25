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

SCENARIO("Multiply each element of the vector by the minimum element")
{
	WHEN("Some elements")
	{
		vector<float> numbers = { 2, 2, 3 };
		MultiplyEachElemenstyWithMinimumElement(numbers);
		REQUIRE(numbers.size() == 3);
		REQUIRE(numbers[0] == 4);
		REQUIRE(numbers[1] == 4);
		REQUIRE(numbers[2] == 6);
	}

	WHEN("Empty vector")
	{
		vector<float> numbers = {};
		MultiplyEachElemenstyWithMinimumElement(numbers);
		REQUIRE(numbers.empty());
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