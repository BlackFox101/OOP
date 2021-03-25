#include <iostream>
#include <vector>
#include <string>
#include "vector.h"

using namespace std;

int main()
{
    vector<float> numbers = ReadVector(cin);

    MultiplyEachElemenstyWithMinimumElement(numbers);

    SortVector(numbers);

    OutputVector(cout, numbers);

    return 0;
}