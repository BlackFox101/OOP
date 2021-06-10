#include "CLineSegment.h"
#include <sstream>
#include <iomanip>
#include <cstdint>

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColour)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColour)
{ }

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return GetDistance(m_startPoint, m_endPoint);;
}

std::string CLineSegment::ToString() const
{
	std::ostringstream output;
	output << "LineSegment with start point: " << m_startPoint << ", end point: " << m_endPoint << "; ";
	output << "Outline color: #" << std::setfill('0') << std::hex << std::setw(6) << m_outlineColor;
	
	return output.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}