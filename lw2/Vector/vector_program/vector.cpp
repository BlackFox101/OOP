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

void MultiplyEachElemenstyWithMinimumElement(vector<float>& numbersVector)
{
    if (numbersVector.empty())
    {
        return;
    }

    vector<float>::iterator result = min_element(numbersVector.begin(), numbersVector.end());
    float min = numbersVector[distance(numbersVector.begin(), result)];

    for (auto& num : numbersVector)
    {
        num = min * num;
    }
}

void OutputVector(ostream& output, vector<float>& vector)
{
    for (auto& i : vector)
    {
        output << round(i * 1000) / 1000 << endl;
    }
}

void SortVector(vector<float>& numbersVector)
{
    sort(numbersVector.begin(), numbersVector.end());
}