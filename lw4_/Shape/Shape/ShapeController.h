#pragma once
#include <vector>
#include <ostream>
#include <stdexcept>
#include <sstream>
#include <memory>
#include "IShape.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CLineSegment.h"

class ShapeController
{
public:
	void PushShape(std::string str);
	void PrintShapeInfoWithLargestArea(std::ostream& output) const;
	void PrintShapeInfoWithSmallestPerimeter(std::ostream& output) const;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;

	std::shared_ptr<CTriangle> GetTriangle(std::stringstream& shapeStream);
	std::shared_ptr<CRectangle> GetRectangle(std::stringstream& shapeStream);
	std::shared_ptr<CCircle> GetCircle(std::stringstream& shapeStream);
	std::shared_ptr<CLineSegment> GetLineSegment(std::stringstream& shapeStream);
	uint32_t GetColor(std::string color);
};

