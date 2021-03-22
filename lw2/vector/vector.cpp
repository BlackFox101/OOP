#include "vector.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<float> ReadVector(istream& input)
{
	vector<float> numbers;

    string str;
    getline(input, str);
    string temp;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
        {
            temp += str[i];
        }
        if (str[i] == ' ' || i == str.length()-1)
        {
            size_t pos;
            float number = stof(temp, &pos);
            if (pos != temp.length())
            {
                cout << "No number entered: " << temp << endl;
                return numbers;
            }

            numbers.push_back(number);
            temp = "";
        }
    }

	return numbers;
}

int FindMinValuePosition(vector<float> numbersVector)
{
    int pos = 0;
    int min = numbersVector[0];

    for (size_t i = 0; i < numbersVector.size(); i++)
    {
        if (min > numbersVector[i])
        {
            min = numbersVector[i];
            pos = i;
        }
    }

    return pos;
}

void MultiplyElementsVector(vector<float>& numbersVector, float value)
{
    float val = round(value * 1000) / 1000;
    for (size_t i = 0; i < numbersVector.size(); i++)
    {
        numbersVector[i] = (round(numbersVector[i] * 1000) / 1000) * val;
    }
}

void OutputVector(ostream& output, vector<float>& vector)
{
    for (auto& i : vector)
    {
        output << i << endl;
    }
}

void SortVector(vector<float>& numbersVector)
{
    sort(numbersVector.begin(), numbersVector.end());
}