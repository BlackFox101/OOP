#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../MyArray/CMyArray.h"

using namespace std;

SCENARIO("String")
{
	WHEN("defalut")
	{
		CMyArray<string> vector;
		REQUIRE(vector.GetSize() == 0);
	}
	WHEN("Size")
	{
		CMyArray<string> vector(5);
		REQUIRE(vector.GetSize() == 5);
	}
	WHEN("Size and value")
	{
		CMyArray<string> vector(3, "Hello");
		REQUIRE(vector.GetSize() == 3);
		CHECK(vector[0] == "Hello");
		CHECK(vector[1] == "Hello");
		CHECK(vector[2] == "Hello");
	}
	WHEN("Resize")
	{
		CMyArray<string> vector(2, "Hello");
		REQUIRE(vector.GetSize() == 2);
		vector.Resize(4);
		CHECK(vector[0] == "Hello");
		CHECK(vector[1] == "Hello");
		CHECK(vector[2] == "");
		CHECK(vector[3] == "");

		vector.Resize(3);
		REQUIRE(vector.GetSize() == 3);
		CHECK(vector[0] == "Hello");
		CHECK(vector[1] == "Hello");
		CHECK(vector[2] == "");
	}
	WHEN("Assignment by index")
	{
		CMyArray<string> vector(1, "Hello");
		vector[0] = "world";
		CHECK(vector[0] == "world");
	}
}

SCENARIO("Int")
{
	WHEN("defalut")
	{
		CMyArray<int> vector;
		REQUIRE(vector.GetSize() == 0);
	}
	WHEN("Size")
	{
		CMyArray<int> vector(5);
		REQUIRE(vector.GetSize() == 5);
	}
	WHEN("Size and value")
	{
		CMyArray<int> vector(3, 2);
		REQUIRE(vector.GetSize() == 3);
		CHECK(vector[0] == 2);
		CHECK(vector[1] == 2);
		CHECK(vector[2] == 2);
	}
	WHEN("Resize")
	{
		CMyArray<int> vector(2, 5);
		REQUIRE(vector.GetSize() == 2);
		vector.Resize(4);
		CHECK(vector[0] == 5);
		CHECK(vector[1] == 5);
		CHECK(vector[2] == 0);
		CHECK(vector[3] == 0);

		vector.Resize(3);
		REQUIRE(vector.GetSize() == 3);
		CHECK(vector[0] == 5);
		CHECK(vector[1] == 5);
		CHECK(vector[2] == 0);
	}
	WHEN("Assignment by index")
	{
		CMyArray<int> vector(1, 1);
		vector[0] = 50;
		CHECK(vector[0] == 50);
	}
}

SCENARIO("Double")
{
	WHEN("defalut")
	{
		CMyArray<double> vector;
		REQUIRE(vector.GetSize() == 0);
	}
	WHEN("Size")
	{
		CMyArray<double> vector(5);
		REQUIRE(vector.GetSize() == 5);
	}
	WHEN("Size and value")
	{
		CMyArray<double> vector(3, 3.14);
		REQUIRE(vector.GetSize() == 3);
		CHECK(vector[0] == 3.14);
		CHECK(vector[1] == 3.14);
		CHECK(vector[2] == 3.14);
	}
	WHEN("Resize")
	{
		CMyArray<double> vector(2, 3.14);
		REQUIRE(vector.GetSize() == 2);
		vector.Resize(4);
		CHECK(vector[0] == 3.14);
		CHECK(vector[1] == 3.14);
		CHECK(vector[2] == 0);
		CHECK(vector[3] == 0);

		vector.Resize(3);
		REQUIRE(vector.GetSize() == 3);
		CHECK(vector[0] == 3.14);
		CHECK(vector[1] == 3.14);
		CHECK(vector[2] == 0);
	}
	WHEN("Assignment by index")
	{
		CMyArray<double> vector(1, 1.1);
		CHECK(vector[0] == 1.1);
		vector[0] = 50.14;
		CHECK(vector[0] == 50.14);
	}
}

SCENARIO("Clear")
{
	CMyArray<int> vector(3, 2);
	REQUIRE(vector.GetSize() == 3);
	vector.Clear();
	REQUIRE(vector.GetSize() == 0);
}

SCENARIO("Create empty vector")
{
	CMyArray<int> vector;
	REQUIRE(vector.GetSize() == 0);
}

SCENARIO("Vector index out of range")
{
	CMyArray<int> vector;
	try
	{
		vector[0];
		CHECK(false);
	}
	catch (const std::exception&)
	{
		CHECK(true);
	}
}

SCENARIO("Create a vector of the desired length without values")
{
	WHEN("Int")
	{
		CMyArray<int> vector(3);
		REQUIRE(vector.GetSize() == 3);
		CHECK(vector[0] == 0);
		CHECK(vector[1] == 0);
		CHECK(vector[2] == 0);
	}
	WHEN("String")
	{
		CMyArray<string> vector(3);
		REQUIRE(vector.GetSize() == 3);
		CHECK(vector[0] == "");
		CHECK(vector[1] == "");
		CHECK(vector[2] == "");
	}
	WHEN("Double")
	{
		CMyArray<double> vector(3);
		REQUIRE(vector.GetSize() == 3);
		CHECK(vector[0] == 0);
		CHECK(vector[1] == 0);
		CHECK(vector[2] == 0);
	}
}

SCENARIO("Iterator begin end")
{
	CMyArray<int> vector;
	vector.PushBack(1);
	vector.PushBack(2);
	vector.PushBack(3);

	CMyArray<int>::iterator it = vector.begin();
	CHECK(*it == 1);
	it = vector.end()-1;
	CHECK(*it == 3);
}

SCENARIO("Iterator operations")
{
	CMyArray<int> vector;
	vector.PushBack(1);
	vector.PushBack(2);
	vector.PushBack(3);
	auto it = vector.begin();
	REQUIRE(*it == 1);

	WHEN("+= -=")
	{ 
		it += 2;
		CHECK(*it == 3);

		it -= 2;
		CHECK(*it == 1);
	}
	WHEN("+ -")
	{
		it = it + 1;
		CHECK(*it == 2);

		it = it - 1;
		CHECK(*it == 1);
	}
	WHEN("++")
	{
		it++;
		CHECK(*it == 2);
	}
	WHEN("--")
	{
		it = vector.end();
		it--;
		CHECK(*it == 3);
	}
	WHEN("==")
	{
		CHECK(vector.begin() == vector.begin());
		CHECK(!(vector.begin() == vector.end()));
	}
	WHEN("!=")
	{
		CHECK(vector.begin() != vector.end());
		CHECK(!(vector.begin() != vector.begin()));
	}
}

SCENARIO("Assigning a value")
{
	CMyArray<int> vector;
	vector.PushBack(1);
	auto it = vector.begin();
	*it = 5;
	CHECK(*it == 5);
}

SCENARIO("Reverse iterator")
{
	CMyArray<int> vector;
	vector.PushBack(1);
	vector.PushBack(2);
	vector.PushBack(3);
	CMyArray<int>::reverse_iterator it = vector.rbegin();
	CHECK(*it == 3);

	it = vector.rend();
	it--;
	CHECK(*it == 1);
}

SCENARIO("Const iterators")
{
	WHEN("const_iterator")
	{
		CMyArray<int> vector;
		vector.PushBack(1);
		vector.PushBack(2);
		vector.PushBack(3);
		CMyArray<int>::const_iterator it = vector.begin();
		CHECK(*it == 1);

		it = vector.end();
		it--;
		CHECK(*it == 3);
	}
	WHEN("const_reverse_iterator")
	{
		CMyArray<int> vector;
		vector.PushBack(1);
		vector.PushBack(2);
		vector.PushBack(3);
		CMyArray<int>::const_reverse_iterator it = vector.rbegin();
		CHECK(*it == 3);

		it = vector.rend();
		it--;
		CHECK(*it == 1);
	}
}