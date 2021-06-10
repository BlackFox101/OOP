#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Shape/CTriangle.h"
#include "../Shape/CRectangle.h"
#include "../Shape/CCircle.h"
#include "../Shape/CLineSegment.h"
#include "../Shape/ShapeController.h"
#include <cmath>

// TODO RENAME
// Передавать разные x и y 
// Передать цвет разный

SCENARIO("Create CTriangle and return arguments")
{
	CTriangle triangle({ -1, 1 }, { -1, -1 }, { 1, -1 }, 0x000000, 0xFFFFFF);

	CHECK(round(triangle.GetArea() * 1000) / 1000 == 2.000);
	CHECK(round(triangle.GetPerimeter() * 1000) / 1000 == 6.828);
	CHECK(triangle.ToString() == "Triangle with vertices: {-1, 1}, {-1, -1}, {1, -1}; Outline color: #000000; Fill color: #ffffff");
	CHECK(triangle.GetOutlineColor() == 0x000000);
	CHECK(triangle.GetFillColor() == 0xFFFFFF);
	CHECK(triangle.GetVertex1().x == -1);
	CHECK(triangle.GetVertex1().y == 1);
	CHECK(triangle.GetVertex2().x == -1);
	CHECK(triangle.GetVertex2().y == -1);
	CHECK(triangle.GetVertex3().x == 1);
	CHECK(triangle.GetVertex3().y == -1);
}

SCENARIO("Create CRectangle and return arguments")
{
	CRectangle rectangle({ -2, 1 }, 3, 2, 0x000000, 0xFFFFFF);

	CHECK(round(rectangle.GetArea() * 1000) / 1000 == 6.000);
	CHECK(round(rectangle.GetPerimeter() * 1000) / 1000 == 10.000);
	CHECK(rectangle.ToString() == "Rectangle with top left point: {-2, 1}, width: 3, height: 2; Outline color: #000000; Fill color: #ffffff");
	CHECK(rectangle.GetOutlineColor() == 0x000000);
	CHECK(rectangle.GetFillColor() == 0xFFFFFF);
	CHECK(rectangle.GetLeftTop().x == -2);
	CHECK(rectangle.GetLeftTop().y == 1);
	CHECK(rectangle.GetRightBottom().x == 1);
	CHECK(rectangle.GetRightBottom().y == -1);
	CHECK(rectangle.GetWidth() == 3);
	CHECK(rectangle.GetHeight() == 2);
}

SCENARIO("Create CCircle and return arguments")
{
	CCircle circle({ 0, 0 }, 3, 0x000000, 0xFFFFFF);

	CHECK(round(circle.GetArea() * 1000) / 1000 == 28.17);
	CHECK(round(circle.GetPerimeter() * 1000) / 1000 == 18.78);
	CHECK(circle.ToString() == "Circle with center point: {0, 0}, radius: 3; Outline color: #000000; Fill color: #ffffff");
	CHECK(circle.GetOutlineColor() == 0x000000);
	CHECK(circle.GetFillColor() == 0xFFFFFF);
	CHECK(circle.GetCenter().x == 0);
	CHECK(circle.GetCenter().y == 0);
	CHECK(circle.GetRadius() == 3);
}

SCENARIO("Create CLineSegment and return arguments")
{
	CLineSegment line({ -1, 1 }, { 1, 1 }, 0x000000);

	CHECK(round(line.GetArea() * 1000) / 1000 == 0);
	CHECK(round(line.GetPerimeter() * 1000) / 1000 == 2.0);
	CHECK(line.ToString() == "LineSegment with start point: {-1, 1}, end point: {1, 1}; Outline color: #000000");
	CHECK(line.GetOutlineColor() == 0x000000);
	CHECK(line.GetStartPoint().x == -1);
	CHECK(line.GetStartPoint().y == 1);
	CHECK(line.GetEndPoint().x == 1);
	CHECK(line.GetEndPoint().y == 1);
}

SCENARIO("PushShape to controller")
{
	ShapeController shapeController;
	std::string str;
	WHEN("OK")
	{
		str = "rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00";
		CHECK_NOTHROW(shapeController.CreateShape(str));

		str = "triangle -1 1 -1 -1 1 -1 ff0000 00ff00";
		CHECK_NOTHROW(shapeController.CreateShape(str));

		str = "circle 0 0 2 ff0000 00ff00";
		CHECK_NOTHROW(shapeController.CreateShape(str));

		str = "line 0 1 1 1 ff0000 00ff00";
		CHECK_NOTHROW(shapeController.CreateShape(str));
	}
	WHEN("Not enough arguments")
	{
		str = "rectangle 20.15 30.7 40.4 ff0000 00ff00";
		CHECK_THROWS(shapeController.CreateShape(str));
	}
	WHEN("Unknown figure")
	{
		
		str = "cub 20.15 30.7 40.4 ff0000 00ff00";
		CHECK_THROWS(shapeController.CreateShape(str));
	}
}

SCENARIO("Get neccesary shapes")
{
	WHEN("ok")
	{
		ShapeController shapeController;
		auto shape = shapeController.CreateShape("rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00");
		shapeController.PushShape(shape);
		shape = shapeController.CreateShape("triangle -1 1 -1 -1 1 -1 ff0000 00ff00");
		shapeController.PushShape(shape);

		std::ostringstream output1;
		shapeController.PrintShapeInfoWithLargestArea(output1);
		CHECK(output1.str() == "Shape with largest area:\nRectangle with top left point: {10.3, 20.15}, width: 30.7, height: 40.4; Outline color: #ff0000; Fill color: #00ff00");

		std::ostringstream output2;
		shapeController.PrintShapeInfoWithSmallestPerimeter(output2);
		CHECK(output2.str() == "Shape with smallest perimeter:\nTriangle with vertices: {-1, 1}, {-1, -1}, {1, -1}; Outline color: #ff0000; Fill color: #00ff00");
	}
	WHEN("No shapes in vector")
	{
		ShapeController shapeController;
		std::ostringstream output;

		shapeController.PrintShapeInfoWithLargestArea(output);
		CHECK(output.str() == "");
		shapeController.PrintShapeInfoWithSmallestPerimeter(output);
		CHECK(output.str() == "");
	}
}