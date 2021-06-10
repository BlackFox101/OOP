#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	size_t maxValueIndex = 0;
	for (size_t i = 1; i < arr.size(); i++)
	{
		if (less(arr[maxValueIndex], arr[i]))
		{
			maxValueIndex = i;
		}
	}
	maxValue = arr[maxValueIndex];
	
	return true;
}