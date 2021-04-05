#include <iostream>
#include <set>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../PrimeNumber/PrimeNumbersGenerator.h"

SCENARIO("StringToInt")
{
	std::ostringstream outputForErrors;

	Error error = Error::NOT_ERROR;
	int number = StringToInt("2", error, outputForErrors);
	CHECK(error == Error::NOT_ERROR);
	CHECK(number == 2);

	error = Error::NOT_ERROR;
	number = StringToInt("1", error, outputForErrors);
	CHECK(error == Error::ARGUMENT_OUT_OF_RANGE);
	CHECK(number == 1);

	error = Error::NOT_ERROR;
	number = StringToInt("2147483648", error, outputForErrors);
	CHECK(error == Error::ARGUMENT_OUT_OF_RANGE);

	error = Error::NOT_ERROR;
	number = StringToInt("2147483647", error, outputForErrors);
	CHECK(error == Error::NOT_ERROR);
	CHECK(number == 2147483647);
}

SCENARIO("CreatePrimeNumberSet")
{
	std::set<int> primeNumbers = {2, 3, 5, 7};
	std::vector<bool> wasPrimeVector = { 0, 1, 1, 0, 1, 0, 1, 0, 0, 0 };
	CHECK(primeNumbers == CreatePrimeNumberSet(wasPrimeVector));
}

SCENARIO("CreateWasPrimeVector")
{
	std::vector<bool> wasPrimeVector = CreateWasPrimeVector(10);
	REQUIRE(wasPrimeVector.size() == 10);

	CHECK(wasPrimeVector[0] == 0);
	CHECK(wasPrimeVector[1] == 1);
	CHECK(wasPrimeVector[2] == 1);
	CHECK(wasPrimeVector[3] == 0);
	CHECK(wasPrimeVector[4] == 1);
	CHECK(wasPrimeVector[5] == 0);
	CHECK(wasPrimeVector[6] == 1);
	CHECK(wasPrimeVector[7] == 0);
	CHECK(wasPrimeVector[8] == 0);
	CHECK(wasPrimeVector[9] == 0);
}

SCENARIO("GeneratePrimeNumbersSet 100000000")
{
	CHECK(5761455 == GeneratePrimeNumbersSet(100000000).size());
}

SCENARIO("OutputErrorMessage")
{
	std::ostringstream output;

	WHEN("Error::NOT_ERROR")
	{
		Error error = Error::NOT_ERROR;
		OutputErrorMessage(output, error);
		CHECK(output.str() == "There are no errors\n");
	}
	WHEN("Error::INVALID_ARGUMENT_COUNT")
	{
		Error error = Error::INVALID_ARGUMENT_COUNT;
		OutputErrorMessage(output, error);
		CHECK(output.str() == "Invalid arguments count\nUsage PrimeNumberGenerator.exe <upper bound>\n");
	}
	WHEN("Error::INVALID_ARGUMENT")
	{
		Error error = Error::INVALID_ARGUMENT;
		OutputErrorMessage(output, error);
		CHECK(output.str() == "Invalid argument(Not a number entered)\n");
	}
	WHEN("Error::ARGUMENT_OUT_OF_RANGE")
	{
		Error error = Error::ARGUMENT_OUT_OF_RANGE;
		OutputErrorMessage(output, error);
		CHECK(output.str() == "Argument out of range\nEnter a number in the range 2 < args <= 2147483647\n");
	}
}

SCENARIO("OutputPrimeNumbers")
{
	std::set<int> primeNumbers = GeneratePrimeNumbersSet(10);
	std::ostringstream output;
	OutputPrimeNumbers(output, primeNumbers);
	CHECK(output.str() == "2 3 5 7 \n");
}

SCENARIO("ParseArgs")
{
	std::ostringstream outputForErrors;
	Error error;
	const int argc = 2;
	char* argv[argc] = { (char*)"PathToProgram", (char*)"100"};
	ParseArgs(argc, argv, error, outputForErrors);
	CHECK(error == Error::NOT_ERROR);
}