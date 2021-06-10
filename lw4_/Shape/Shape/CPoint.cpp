#include "CPoint.h"
#include <cmath>

double GetDistance(const CPoint& left, const CPoint& right)
{
	return sqrt((right.x - left.x) * (right.x - left.x) + (right.y - left.y) * (right.y - left.y));
}

std::ostream& operator<<(std::ostream& stream, const CPoint& point)
{
	return stream << "{" << point.x << ", " << point.y << "}";
}