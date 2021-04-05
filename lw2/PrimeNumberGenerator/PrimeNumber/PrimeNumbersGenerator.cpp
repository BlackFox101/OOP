#include "PrimeNumbersGenerator.h"

using namespace std;

set<int> CreatePrimeNumberSet(const vector<bool>& wasPrimeVector)
{
	set<int> primeNumbers;
	int number = 1;
	for (auto const& wasPrime : wasPrimeVector)
	{
		if (wasPrime)
		{
			primeNumbers.insert(number);
		}
		++number;
	}
	
	return primeNumbers;
}

vector<bool> CreateWasPrimeVector(int upperBound)
{
	vector<bool> wasPrimeVector(upperBound, true);
	wasPrimeVector[0] = false;

	for (size_t i = 0; i < wasPrimeVector.size(); ++i)
	{
		if (wasPrimeVector[i])
		{
			for (size_t j = i+1 + i; j < wasPrimeVector.size(); j = j + i+1)
			{
				wasPrimeVector[j] = false;
			}
		}
	}

	return wasPrimeVector;
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> wasPrimeVector = CreateWasPrimeVector(upperBound);

	set<int> primeNumbers = CreatePrimeNumberSet(wasPrimeVector);

	return primeNumbers;
}

int StringToInt(const string& str, Error& error, ostream& outputForErrors)
{
    size_t pos;
	int number = -1;
	try
	{
		number = stoi(str, &pos);
		if (pos != str.length())
		{
			error = Error::INVALID_ARGUMENT;
		}
	}
	catch(const out_of_range&)
	{
		error = Error::ARGUMENT_OUT_OF_RANGE;
	}

	if (number < 2)
	{
		error = Error::ARGUMENT_OUT_OF_RANGE;
	}
	
	if (error != Error::NOT_ERROR)
	{
		OutputErrorMessage(outputForErrors, error);
	}

    return number;
}

void OutputErrorMessage(ostream& output, Error error)
{
	switch (error)
	{
	case Error::NOT_ERROR:
			output << "There are no errors\n";
			break;
	case Error::INVALID_ARGUMENT_COUNT:
			output << "Invalid arguments count\n";
			output << "Usage PrimeNumberGenerator.exe <upper bound>\n";
			break;
	case Error::INVALID_ARGUMENT:
			output << "Invalid argument(Not a number entered)\n";
			break;
	case Error::ARGUMENT_OUT_OF_RANGE:
			output << "Argument out of range\n";
			output << "Enter a number in the range 2 < args <= 2147483647\n";
			break;
	}
}

void OutputPrimeNumbers(ostream& output, const set<int>& primeNumbers)
{
	for (auto const& wasPrime : primeNumbers)
	{
		output << wasPrime << " ";
	}
	output << "\n";
}

optional<Args> ParseArgs(int argc, char* argv[], Error& error, ostream& outputForErrors)
{
	error = Error::NOT_ERROR;
	if (argc != 2)
	{
		error = Error::INVALID_ARGUMENT_COUNT;
		return nullopt;
	}
	Args args;
	args.upperBound = StringToInt(argv[1], error, outputForErrors);
	if (error == Error::NOT_ERROR)
	{
		return args;
	}

	return nullopt;
}