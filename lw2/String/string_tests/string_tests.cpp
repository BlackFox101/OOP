#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../string_program/html_decode.h"

SCENARIO("HtmlEntityToChar")
{
	std::string str;
	HtmlEntityToChar(str, "&quot;");
	CHECK(str == "\"");

	str = "";
	HtmlEntityToChar(str, "&apos;");
	CHECK(str == "’");

	str = "";
	HtmlEntityToChar(str, "&lt;");
	CHECK(str == "<");

	str = "";
	HtmlEntityToChar(str, "&gt;");
	CHECK(str == ">");

	str = "";
	HtmlEntityToChar(str, "&amp;");
	CHECK(str == "&");

	str = "";
	HtmlEntityToChar(str, "214124 &");
	CHECK(str == "214124 &");
}

SCENARIO("HTML Decode")
{
	CHECK(HtmlDecode("123") == "123");

	CHECK(HtmlDecode("&quot;") == "\"");
	CHECK(HtmlDecode("&apos;") == "’");
	CHECK(HtmlDecode("&lt;") == "<");
	CHECK(HtmlDecode("&gt;") == ">");
	CHECK(HtmlDecode("&amp;") == "&");

	CHECK(HtmlDecode("&&amp;") == "&&");
	CHECK(HtmlDecode("&&lt;Hello&gt;") == "&<Hello>");

	CHECK(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M’s");
}

SCENARIO("HTML Decode lines")
{
	std::ostringstream output;

	WHEN("\"")
	{
		std::istringstream input("&quot;");
		HtmlDecodeLines(input, output);
		CHECK(output.str() == "\"");
		CHECK(input.eof());
	}

	WHEN("&")
	{
		std::istringstream input("&apos;");
		HtmlDecodeLines(input, output);
		CHECK(output.str() == "’");
		CHECK(input.eof());
	}

	WHEN("\"")
	{
		std::istringstream input("&lt;");
		HtmlDecodeLines(input, output);
		CHECK(output.str() == "<");
		CHECK(input.eof());
	}
}