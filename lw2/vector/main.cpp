#include <iostream>
#include <vector>
#include <string>
#include "vector.h"

using namespace std;

int main()
{
    vector<float> numbers = ReadVector(cin);

    MultiplyElementsVector(numbers, numbers[FindMinValuePosition(numbers)]);

    SortVector(numbers);

    OutputVector(cout, numbers);

    return 0;
}