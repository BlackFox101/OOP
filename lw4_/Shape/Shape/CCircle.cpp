#include "CCircle.h"
#include <sstream>
#include <iomanip>
#include <cstdint>

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColour, uint32_t fillColour)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColour(outlineColour)
	, m_fillColour(fillColour)
{ }

double CCircle::GetArea() const
{
	return PI * m_radius * m_radius;
}
double CCircle::GetPerimeter() const
{
	return 2 * PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::ostringstream output;
	output << "Circle with center point: " << m_center << ", radius: " << m_radius << "; ";
	output << std::setfill('0') << std::hex;
	output << "Outline color: #" << std::setw(6) << m_outlineColour << "; ";
	output << "Fill color: #" << std::setw(6) << m_fillColour;

	return output.str();
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColour;
}
uint32_t CCircle::GetFillColor() const
{
	return m_fillColour;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}