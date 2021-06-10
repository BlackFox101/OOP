#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../MyString/CMyString.h"

using namespace std;

SCENARIO("Constructors")
{
	WHEN("Default constructor")
	{
		CMyString str;
		REQUIRE(str.GetLength() == 0);
		REQUIRE(str == "");
	}
	WHEN("Constructor that initializes a string with string data")
	{
		CMyString str("Hello");
		REQUIRE(str.GetLength() == 5);
		REQUIRE(str == "Hello");
	}
	WHEN("Constructor that initializes a string with data from a character array of a given length")
	{
		CMyString str("Hello", 3);
		REQUIRE(str.GetLength() == 3);
		REQUIRE(str == "Hel");
	}
	WHEN("Copy Constructor")
	{
		CMyString str1("Hello");
		CMyString str2(str1);
		REQUIRE(str2.GetLength() == 5);
		REQUIRE(str2 == "Hello");
	}
	WHEN("Constructor that initializes a string with data from a standard library string")
	{
		CMyString str2("Hello"s);
		REQUIRE(str2.GetLength() == 5);
		REQUIRE(str2 == "Hello");
	}
}

SCENARIO("GetStringData")
{
	CMyString str2 = "Hello";
	REQUIRE(str2.GetStringData() == "Hello"s);
}

SCENARIO("SubString")
{
	CMyString str1("Hello");
	CMyString str2 = str1.SubString(0, 5);
	REQUIRE(str2 == "Hello");

	str2 = str1.SubString(1, 4);
	REQUIRE(str2 == "ell");

	str2 = str1.SubString(0, 0);
	REQUIRE(str2 == "");
}

SCENARIO("Clear")
{
	CMyString str("Hello");
	str.Clear();
	REQUIRE(str.GetLength() == 0);
	REQUIRE(str == "");
}

SCENARIO(" += ")
{
	CMyString str1("Hello");
	CMyString str2(" world!");
	str1 += str2;
	REQUIRE(str1 == "Hello world!");
	REQUIRE(str2 == " world!");

	str1 = "";
	str1 += "temp";
	REQUIRE(str1 == "temp");
}

SCENARIO(" + ")
{
	CMyString str1("Hello");
	CMyString str2(" world!");

	CMyString str = str1 + str2;
	REQUIRE(str == "Hello world!");

	str = "Hello"s + str2;
	REQUIRE(str == "Hello world!");

	str = "Hello" + str2;
	REQUIRE(str == "Hello world!");
}

SCENARIO(" String comparison ")
{
	WHEN(" == ")
	{
		CMyString str1("Hello");
		CMyString str2("Hello");
		CHECK(str1 == str2);

		str2 = "123";
		CHECK(!(str1 == str2));
	}
	WHEN(" != ")
	{
		CMyString str1("Hello");
		CMyString str2("123");
		CHECK(str1 != str2);

		str2 = "Hello";
		CHECK(!(str1 != str2));
	}
	WHEN(" > ")
	{
		CMyString str1("abcd");
		CMyString str2("adc");
		CHECK(str1 > str2);

		str2 = "abcd";
		CHECK(!(str1 > str2));
	}
	WHEN(" >= ")
	{
		CMyString str1("abcd");
		CMyString str2("adc");
		CHECK(str1 >= str2);

		str2 = "abcd";
		CHECK(str1 >= str2);
	}
	WHEN(" < ")
	{
		CMyString str1("abc");
		CMyString str2("adcd");
		CHECK(str1 < str2);

		str2 = "abc";
		CHECK(!(str1 < str2));
	}
	WHEN(" <= ")
	{
		CMyString str1("abc");
		CMyString str2("adcd");
		CHECK(str1 <= str2);

		str2 = "abc";
		CHECK(str1 <= str2);
	}
}

// тест по < не проходит при !(zubra < zebr);
// Утечки памяти при subString, operator+=,
// При + двойное копирование

SCENARIO(" [] ")
{
	WHEN(" [] ")
	{
		CMyString str1("abc");
		CHECK(str1[0] == 'a');
	}
	WHEN(" [] = ")
	{
		CMyString str1("abc");
		str1[0] = 'A';
		CHECK(str1[0] == 'A');
		CHECK(str1.GetStringData() == "Abc"s);
	}
}

SCENARIO(" <<, >>")
{
	WHEN(" << ")
	{
		std::ostringstream output;
		CMyString string = "Hello";

		output << string;
		CHECK(output.str() == "Hello");
	}
	WHEN(" >> ")
	{
		std::istringstream input("Hello");
		CMyString str;
		input >> str;
		CHECK(str == "Hello"s);
	}
}