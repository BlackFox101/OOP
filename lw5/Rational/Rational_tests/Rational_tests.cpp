#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Rational/CRational.h"

SCENARIO("Checking the normalized number preservation")
{
	WHEN("Without parameters")
	{
		CRational number;
		CHECK(number.GetNumerator() == 0);
		CHECK(number.GetDenominator() == 1);
	}
	WHEN("One parameter is positive")
	{
		CRational number(5);
		CHECK(number.GetNumerator() == 5);
	}
	WHEN("One parameter is negative")
	{
		CRational number(-5);
		CHECK(number.GetNumerator() == -5);
	}
	WHEN("Two parameters, one is negative")
	{
		CRational number(-3, 5);
		CHECK(number.GetNumerator() == -3);
		CHECK(number.GetDenominator() == 5);
	}
	WHEN("Two parameters, both negative")
	{
		CRational number(-3, -5);
		CHECK(number.GetNumerator() == 3);
		CHECK(number.GetDenominator() == 5);
	}

	WHEN("There is a common divisor")
	{
		CRational number(6, 10);
		CHECK(number.GetNumerator() == 3);
		CHECK(number.GetDenominator() == 5);
		
		CRational n(10, 5);
		CHECK(n.GetNumerator() == 2);
		CHECK(n.GetDenominator() == 1);
	}
}

SCENARIO("Output of a mixed fraction")
{
	WHEN("Positive number")
	{
		CRational number(10, 5);
		auto compoundFraction = number.ToCompoundFraction();
		REQUIRE(compoundFraction.first == 2);
		REQUIRE(compoundFraction.second.GetNumerator() == 0);
		REQUIRE(compoundFraction.second.GetDenominator() == 1);
	}
	WHEN("Negative number")
	{
		CRational number(-10, 5);
		auto compoundFraction = number.ToCompoundFraction();
		REQUIRE(compoundFraction.first == -2);
		REQUIRE(compoundFraction.second.GetNumerator() == 0);
		REQUIRE(compoundFraction.second.GetDenominator() == 1);
	}
}

SCENARIO("Unary operations +, -")
{
	WHEN(" - ")
	{
		CRational a(3, 5);
		CHECK(-a.GetNumerator() == -3);

		CRational b(-3, 5);
		CHECK(-b.GetNumerator() == 3);
	}
	WHEN(" +")
	{
		CRational a(3, 5);
		CHECK(+a.GetNumerator() == 3);

		CRational b(-3, 5);
		CHECK(+b.GetNumerator() == -3);
	}
}

SCENARIO(" +=, -=, *=, /=")
{
	WHEN(" += ")
	{
		CRational a(3, 5);
		CRational b(7, 8);
		a += b;

		CHECK(a.GetNumerator() == 59);
		CHECK(a.GetDenominator() == 40);

		CRational c(1, 2);
		c += 1;
		CHECK(c.GetNumerator() == 3);
		CHECK(c.GetDenominator() == 2);
	}
	WHEN(" -=, ")
	{
		CRational a(1, 2);
		CRational b(1, 6);
		a -= b;

		CHECK(a.GetNumerator() == 1);
		CHECK(a.GetDenominator() == 3);


		CRational c(1, 2);
		c -= 1;
		CHECK(c.GetNumerator() == -1);
		CHECK(c.GetDenominator() == 2);
	}
	WHEN(" *=, ")
	{
		THEN("Both are positive")
		{
			CRational a(1, 2);
			CRational b(2, 3);
			a *= b;

			CHECK(a.GetNumerator() == 1);
			CHECK(a.GetDenominator() == 3);

			CRational c(1, 2);
			c *= 3;
			CHECK(c.GetNumerator() == 3);
			CHECK(c.GetDenominator() == 2);
		}
		THEN("One negative")
		{
			CRational a(3, 5);
			CRational b(-7, 8);
			a *= b;

			CHECK(a.GetNumerator() == -21);
			CHECK(a.GetDenominator() == 40);

			CRational c(1, 2);
			c *= 3;
			CHECK(c.GetNumerator() == 3);
			CHECK(c.GetDenominator() == 2);
		}
		THEN("Both negative")
		{
			CRational a(-3, 5);
			CRational b(-7, 8);
			a *= b;

			CHECK(a.GetNumerator() == 21);
			CHECK(a.GetDenominator() == 40);

			CRational c(-1, 2);
			c *= -3;
			CHECK(c.GetNumerator() == 3);
			CHECK(c.GetDenominator() == 2);
		}
	}
	WHEN(" /= ")
	{
		THEN("Both are positive")
		{
			CRational a(1, 2);
			CRational b(2, 3);
			a /= b;

			CHECK(a.GetNumerator() == 3);
			CHECK(a.GetDenominator() == 4);

			CRational c(1, 2);
			c /= 3;
			CHECK(c.GetNumerator() == 1);
			CHECK(c.GetDenominator() == 6);
		}
		THEN("One negative")
		{
			CRational a(3, 5);
			CRational b(-7, 8);
			a /= b;

			CHECK(a.GetNumerator() == -24);
			CHECK(a.GetDenominator() == 35);

			CRational c(1, 2);
			c /= -3;
			CHECK(c.GetNumerator() == -1);
			CHECK(c.GetDenominator() == 6);
		}
		THEN("Both negative")
		{
			CRational a(-3, 5);
			CRational b(-7, 8);
			a /= b;

			CHECK(a.GetNumerator() == 24);
			CHECK(a.GetDenominator() == 35);

			CRational c(-1, 2);
			c /= -3;
			CHECK(c.GetNumerator() == 1);
			CHECK(c.GetDenominator() == 6);
		}
	}
}

SCENARIO("Binary operations")
{
	WHEN(" + ")
	{
		CRational a(1, 2);
		CRational b(1, 6);
		CRational � = a + b;

		CHECK(�.GetNumerator() == 2);
		CHECK(�.GetDenominator() == 3);

		� = a + 1;
		CHECK(�.GetNumerator() == 3);
		CHECK(�.GetDenominator() == 2);

		� = 1 + a;
		CHECK(�.GetNumerator() == 3);
		CHECK(�.GetDenominator() == 2);
	}
	WHEN(" - ")
	{
		CRational a(1, 2);
		CRational b(1, 6);
		CRational � = a - b;

		CHECK(�.GetNumerator() == 1);
		CHECK(�.GetDenominator() == 3);

		� = a - 1;
		CHECK(�.GetNumerator() == -1);
		CHECK(�.GetDenominator() == 2);

		� = 1 - a;
		CHECK(�.GetNumerator() == 1);
		CHECK(�.GetDenominator() == 2);
	}
	WHEN(" * ")
	{
		CRational a(1, 2);
		CRational b(2, 3);
		CRational � = a * b;

		CHECK(�.GetNumerator() == 1);
		CHECK(�.GetDenominator() == 3);

		� = a * -3;
		CHECK(�.GetNumerator() == -3);
		CHECK(�.GetDenominator() == 2);

		� = 7 * b;
		CHECK(�.GetNumerator() == 14);
		CHECK(�.GetDenominator() == 3);
	}
	WHEN(" / ")
	{
		CRational a(1, 2);
		CRational b(2, 3);
		CRational � = a / b;

		CHECK(�.GetNumerator() == 3);
		CHECK(�.GetDenominator() == 4);

		� = a / 5;
		CHECK(�.GetNumerator() == 1);
		CHECK(�.GetDenominator() == 10);

		� = 7 / b;
		CHECK(�.GetNumerator() == 21);
		CHECK(�.GetDenominator() == 2);
	}
}

SCENARIO("Comparison operators")
{
	WHEN(" == ")
	{
		CRational a(1, 2);
		CHECK(a == a);

		CRational b(4, 1);
		CHECK(!(a == b));

		CHECK(b == 4);
	}
	WHEN(" != ")
	{
		CRational a(1, 2);
		CHECK(!(a != a));

		CRational b(1, 6);
		CHECK(a != b);

		CHECK(b != 2);
	}

	WHEN(" < ")
	{
		CRational a(1, 2);
		CRational b(1, 3);
		CHECK(b < a);
		CHECK(!(a < b));

		CHECK(a < 7);
		CHECK(!(7 < a));
	}
	WHEN(" <= ")
	{
		CRational a(1, 2);
		CRational b(1, 3);
		CRational c(1, 3);
		CHECK(b <= a);
		CHECK(b <= c);

		CRational d(2, 2);
		CHECK(d <= 1);
		CHECK(1 <= d);
	}
	WHEN(" > ")
	{
		CRational a(1, 2);
		CRational b(1, 3);
		CHECK(a > b);

		CHECK(!(a > 7));
		CHECK(7 > a);
	}
	WHEN(" >= ")
	{
		CRational a(1, 2);
		CRational b(1, 3);
		CRational c(1, 3);
		CHECK(a >= b);
		CHECK(c >= b);

		CRational d(2, 2);
		CHECK(1 >= d);
		CHECK(!(a >= 1));
	}
}

SCENARIO("Input and output operator")
{
	WHEN(" << ")
	{
		std::ostringstream output;
		CRational a(1, 2);
		output << a;
		CHECK(output.str() == "1/2");
	}
	WHEN(" >> ")
	{
		THEN("Valid number")
		{
			std::istringstream input("1/2");
			CRational a;
			input >> a;
			REQUIRE(a.GetNumerator() == 1);
			REQUIRE(a.GetDenominator() == 2);
		}
		THEN("Not a valid number")
		{
			std::istringstream input("1/");
			CRational a;
			input >> a;
			CHECK(input.fail());
		}
		THEN("Not a valid number")
		{
			std::istringstream input("1 / 1");
			CRational a;
			input >> a;
			CHECK(input.fail());
		}
	}
}
