#pragma once
#include <iosfwd>
#include <vector>

using namespace std;

vector<float> ReadVector(istream& input);

int FindMinValuePosition(vector<float> numbers);

void MultiplyElementsVector(vector<float>& numbers, float value);

void SortVector(vector<float>& numbersVector);

void OutputVector(ostream& output, vector<float>& numbers);