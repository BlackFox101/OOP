#include "PrimeNumbersGenerator.h"
#include <ctime>

int main(int argc, char* argv[])
{
    //unsigned int start_time = clock();
    Error error;
    auto args = ParseArgs(argc, argv, error, std::cout);
    if (error != Error::NOT_ERROR)
    {
        return 1;
    }

    GeneratePrimeNumbersSet(args->upperBound);
    OutputPrimeNumbers(std::cout, GeneratePrimeNumbersSet(args->upperBound));
    //unsigned int end_time = clock();
    //unsigned int search_time = end_time - start_time;
    //std::cout << "\n" << search_time << "\n";

    return 0;
}