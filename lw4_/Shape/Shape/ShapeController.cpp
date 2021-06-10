#include "ShapeController.h"
#include <algorithm>

using namespace std;

void ShapeController::PushShape(std::string str)
{
	stringstream shapeStream;
	shapeStream << str;

	string shapeName;
	shapeStream >> shapeName;
	if (shapeName == "triangle")
	{
		m_shapes.push_back(GetTriangle(shapeStream));
	}
	else if (shapeName == "rectangle")
	{
		m_shapes.push_back(GetRectangle(shapeStream));
	}
	else if (shapeName == "circle")
	{
		m_shapes.push_back(GetCircle(shapeStream));
	}
	else if (shapeName == "line")
	{
		m_shapes.push_back(GetLineSegment(shapeStream));
	}
	else
	{
		throw invalid_argument("Unknown figure");
	}
}

shared_ptr<CTriangle> ShapeController::GetTriangle(stringstream& shapeStream)
{
	vector<CPoint> trianglePoints;
	for (size_t i = 0; i < 3; i++)
	{
		double x, y;
		shapeStream >> x >> y;
		if (shapeStream.fail())
		{
			throw invalid_argument("Not enough arguments");
		}
		trianglePoints.push_back({ x , y});
	}

	string outlineStringColour, fillStringColour;
	shapeStream >> outlineStringColour >> fillStringColour;
	if (shapeStream.fail())
	{
		throw invalid_argument("Not enough arguments");
	}
	// TODO: побитовый сдвиг
	uint32_t outlineColour = GetColor(outlineStringColour);
	uint32_t fillColour = GetColor(fillStringColour);

	CTriangle triangle(trianglePoints[0], trianglePoints[1], trianglePoints[2], outlineColour, fillColour);

	return make_shared<CTriangle>(triangle);
}

shared_ptr<CRectangle> ShapeController::GetRectangle(std::stringstream& shapeStream)
{
	double x, y, width, height;
	string outlineStringColour, fillStringColour;
	shapeStream >> x >> y >> width >> height >> outlineStringColour >> fillStringColour;
	if (shapeStream.fail())
	{
		throw invalid_argument("Not enough arguments");
	}

	uint32_t outlineColour = GetColor(outlineStringColour);
	uint32_t fillColour = GetColor(fillStringColour);

	CRectangle rectangle({ x, y }, width, height, outlineColour, fillColour);

	return make_shared<CRectangle>(rectangle);
}

shared_ptr<CCircle> ShapeController::GetCircle(std::stringstream& shapeStream)
{
	double x, y, radius;
	string outlineStringColour, fillStringColour;
	shapeStream >> x >> y >> radius >> outlineStringColour >> fillStringColour;
	if (shapeStream.fail())
	{
		throw invalid_argument("Not enough arguments");
	}
	uint32_t outlineColour = GetColor(outlineStringColour);
	uint32_t fillColour = GetColor(fillStringColour);

	CCircle circle({ x, y }, radius, outlineColour, fillColour);

	return make_shared<CCircle>(circle);
}

shared_ptr<CLineSegment> ShapeController::GetLineSegment(std::stringstream& shapeStream)
{
	double x1, y1, x2, y2;
	string outlineStringColour;
	shapeStream >> x1 >> y1 >> x2 >> y2 >> outlineStringColour;
	if (shapeStream.fail())
	{
		throw invalid_argument("Not enough arguments");
	}
	uint32_t outlineColour = GetColor(outlineStringColour);

	CLineSegment line({ x1, y1 }, { x2, y2 }, outlineColour);

	return make_shared<CLineSegment>(line);
}

uint32_t ShapeController::GetColor(string colorAsString)
{
	try
	{
		uint32_t color = stoi(colorAsString, nullptr, 16);

		return color;
	}
	catch (...)
	{
		throw invalid_argument("Invalid color");
	}
}

void ShapeController::PrintShapeInfoWithLargestArea(ostream& output) const
{
	if (m_shapes.empty())
	{
		return;
	}

	auto maxAreaShape = std::max_element(m_shapes.begin(), m_shapes.end(), [](shared_ptr<IShape> left, shared_ptr<IShape> right) {
		return left->GetArea() < right->GetArea();
	});
	
	output << "Shape with largest area:\n";
	output << (*maxAreaShape)->ToString();
}

void ShapeController::PrintShapeInfoWithSmallestPerimeter(ostream& output) const
{
	if (m_shapes.empty())
	{
		return;
	}

	auto minPerimeterShape = std::min_element(m_shapes.begin(), m_shapes.end(), [](shared_ptr<IShape> left, shared_ptr<IShape> right) {
		return left->GetPerimeter() < right->GetPerimeter();
	});
	output << "Shape with smallest perimeter:\n";
	output << (*minPerimeterShape)->ToString();
}