#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <optional>

enum class Error
{
	NOT_ERROR,
	INVALID_ARGUMENT,
	INVALID_ARGUMENT_COUNT,
	ARGUMENT_OUT_OF_RANGE
};

struct Args
{
	int upperBound;
};

std::set<int> CreatePrimeNumberSet(const std::vector<bool>& wasPrimeVector);

std::vector<bool> CreateWasPrimeVector(int upperBound);

std::set<int> GeneratePrimeNumbersSet(int upperBound);

int StringToInt(const std::string& str, Error& error, std::ostream& outputForErrors);

void OutputErrorMessage(std::ostream& output, Error error);

std::optional<Args> ParseArgs(int argc, char* argv[], Error& error, std::ostream& outputForErrors);

void OutputPrimeNumbers(std::ostream& output, const std::set<int>& primeNumbers);