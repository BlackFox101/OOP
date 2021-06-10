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
	void PushShape(std::shared_ptr<IShape> shape);
	std::shared_ptr<IShape> CreateShape(const std::string& str) const;
	void PrintShapeInfoWithLargestArea(std::ostream& output) const;
	void PrintShapeInfoWithSmallestPerimeter(std::ostream& output) const;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;

	std::shared_ptr<CTriangle> CreateTriangle(std::stringstream& shapeStream) const;
	std::shared_ptr<CRectangle> CreateRectangle(std::stringstream& shapeStream) const;
	std::shared_ptr<CCircle> CreateCircle(std::stringstream& shapeStream) const;
	std::shared_ptr<CLineSegment> CreateLineSegment(std::stringstream& shapeStream) const;
	uint32_t GetColor(const std::string& colorAsString) const;
};

