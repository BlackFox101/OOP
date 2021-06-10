#pragma once
#include <iostream>

class CPoint
{
public:
	double x;
	double y;
};

double GetDistance(const CPoint& left, const CPoint& right);

std::ostream& operator<<(std::ostream& stream, const CPoint& point);