#pragma once
#include <iosfwd>
#include <vector>

using namespace std;

vector<float> ReadVector(istream& input);

void MultiplyEachElemenstyWithMinimumElement(vector<float>& numberVector);

void SortVector(vector<float>& numbersVector);

void OutputVector(ostream& output, vector<float>& vector);