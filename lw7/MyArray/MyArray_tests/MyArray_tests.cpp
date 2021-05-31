#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../MyArray/CMyArray.h"

using namespace std;

SCENARIO("CMyArray")
{
	WHEN("String")
	{
		THEN("defalut")
		{
			CMyArray<string> vector;
			REQUIRE(vector.GetSize() == 0);
		}
		THEN("Size")
		{
			CMyArray<string> vector(5);
			REQUIRE(vector.GetSize() == 5);
		}
		THEN("Size and value")
		{
			CMyArray<string> vector(3, "hello");
			REQUIRE(vector.GetSize() == 3);
			CHECK(vector[1] == "Hello");
			CHECK(vector[2] == "Hello");
			CHECK(vector[3] == "Hello");
		}
		/*THEN("Resize")
		{
			CMyArray<string> vector(2, "hello");
			REQUIRE(vector.GetSize() == 2);
			vector.Resize(4);
			CHECK(vector[1] == "Hello");
			CHECK(vector[2] == "Hello");
			CHECK(vector[3] == "");
			CHECK(vector[4] == "");

			vector.Resize(3);
			REQUIRE(vector.GetSize() == 3);
		}*/
	}
	WHEN("Int")
	{
		THEN("defalut")
		{
			CMyArray<int> vector;
			REQUIRE(vector.GetSize() == 0);
		}
		THEN("Size")
		{
			CMyArray<int> vector(5);
			REQUIRE(vector.GetSize() == 5);
		}
		THEN("Size and value")
		{
			CMyArray<int> vector(3, 2);
			REQUIRE(vector.GetSize() == 3);
			CHECK(vector[1] == 2);
			CHECK(vector[2] == 2);
			CHECK(vector[3] == 2);
		}
		/*THEN("Resize")
		{
			CMyArray<int> vector(2, 5);
			REQUIRE(vector.GetSize() == 2);
			vector.Resize(4);
			CHECK(vector[1] == 5);
			CHECK(vector[2] == 5);
			CHECK(vector[3] == 0);
			CHECK(vector[4] == 0);

			vector.Resize(3);
			REQUIRE(vector.GetSize() == 3);
		}*/
	}
	WHEN("Double")
	{
		THEN("defalut")
		{
			CMyArray<double> vector;
			REQUIRE(vector.GetSize() == 0);
		}
		THEN("Size")
		{
			CMyArray<double> vector(5);
			REQUIRE(vector.GetSize() == 5);
		}
		THEN("Size and value")
		{
			CMyArray<double> vector(3, 3.14);
			REQUIRE(vector.GetSize() == 3);
			CHECK(vector[1] == 3.14);
			CHECK(vector[2] == 3.14);
			CHECK(vector[3] == 3.14);
		}
		/*THEN("Resize")
		{
			CMyArray<double> vector(2, 3.14);
			REQUIRE(vector.GetSize() == 2);
			vector.Resize(4);
			CHECK(vector[1] == 3.14);
			CHECK(vector[2] == 3.14);
			CHECK(vector[3] == 0);
			CHECK(vector[4] == 0);

			vector.Resize(3);
			REQUIRE(vector.GetSize() == 3);
		}*/
	}
}