#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../string_program/html_decode.h"

SCENARIO("String Replace")
{
	REQUIRE(StringReplacer("", "123", ",") == "");
	REQUIRE(StringReplacer("12345", "", ",") == "12345");
	REQUIRE(StringReplacer("1 2 3 4 5", " ", ",") == "1,2,3,4,5");
}

SCENARIO("HTML Decode")
{
	REQUIRE(HtmlDecode("123") == "123");

	REQUIRE(HtmlDecode("&quot;") == "\"");
	REQUIRE(HtmlDecode("&apos;") == "’");
	REQUIRE(HtmlDecode("&lt;") == "<");
	REQUIRE(HtmlDecode("&gt;") == ">");
	REQUIRE(HtmlDecode("&amp;") == "&");

	REQUIRE(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M’s");
}