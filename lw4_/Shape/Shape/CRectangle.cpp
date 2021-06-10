#include "CRectangle.h"
#include <sstream>
#include <iomanip>
#include <cstdint>

CRectangle::CRectangle(CPoint topLeft, double width, double height, uint32_t outlineColour, uint32_t fillColour)
	: m_topLeft(topLeft)
	, m_width(width)
	, m_height(height)
	, m_outlineColour(outlineColour)
	, m_fillColour(fillColour)
{ }

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

std::string CRectangle::ToString() const
{
	std::ostringstream output;
	output << "Rectangle with top left point: " << m_topLeft << ", width: " << m_width << ", height: " << m_height << "; ";
	output << std::setfill('0') << std::hex;
	output << "Outline color: #" << std::setw(6) << m_outlineColour << "; ";
	output << "Fill color: #" << std::setw(6) << m_fillColour;

	return output.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColour;
}
uint32_t CRectangle::GetFillColor() const
{
	return m_fillColour;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_topLeft;
}
CPoint CRectangle::GetRightBottom() const
{
	return { m_topLeft.x + m_width, m_topLeft.y - m_height };
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}