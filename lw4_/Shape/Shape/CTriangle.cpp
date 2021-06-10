#pragma once
#include "CTriangle.h"
#include <sstream>
#include <iomanip>
#include <cstdint>

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const uint32_t& outlineColour, const uint32_t& fillColour)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColour(outlineColour)
	, m_fillColour(fillColour)
{ }

double CTriangle::GetArea() const
{
	double a = GetDistance(m_vertex1, m_vertex2);
	double b = GetDistance(m_vertex2, m_vertex3);
	double c = GetDistance(m_vertex3, m_vertex1);
	double p = 0.5 * (a + b + c);

	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	double a = GetDistance(m_vertex1, m_vertex2);
	double b = GetDistance(m_vertex2, m_vertex3);
	double c = GetDistance(m_vertex3, m_vertex1);

	return a + b + c;
}
std::string CTriangle::ToString() const
{
	std::ostringstream output;
	output << "Triangle with vertices: " << m_vertex1 << ", " << m_vertex2 << ", " << m_vertex3 << "; ";
	output << std::setfill('0') << std::hex;
	output << "Outline color: #" << std::setw(6) << m_outlineColour << "; ";
	output << "Fill color: #" << std::setw(6) << m_fillColour;

	return output.str();
}
uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColour;
}
uint32_t CTriangle::GetFillColor() const
{
	return m_fillColour;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}
CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}
CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}