#include <iostream>
#include "ShapeController.h"
#include <iomanip>
#include <cstdint>

using namespace std;

// TODO: использовать умные указатели
int main()
{
    ShapeController shapeController;

    string line;
    while (getline(cin, line))
    {
		try
		{
			shapeController.PushShape(shapeController.CreateShape(line));
			cout << "The shape was saved successfully\n";
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
		}
    }

	shapeController.PrintShapeInfoWithLargestArea(cout);
	cout << endl;
	shapeController.PrintShapeInfoWithSmallestPerimeter(cout);
	cout << endl;
}
/*
rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00
triangle -1 1 -1 -1 1 -1 ff0000 00ff00
*/