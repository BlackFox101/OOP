#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../string_program/html_decode.h"

SCENARIO("String Replace")
{
	CHECK(StringReplacer("", "123", ",") == "");
	CHECK(StringReplacer("12345", "", ",") == "12345");
	CHECK(StringReplacer("1 2 3 4 5", " ", ",") == "1,2,3,4,5");
}

SCENARIO("HTML Decode")
{
	CHECK(HtmlDecode("123") == "123");

	CHECK(HtmlDecode("&quot;") == "\"");
	CHECK(HtmlDecode("&apos;") == "’");
	CHECK(HtmlDecode("&lt;") == "<");
	CHECK(HtmlDecode("&gt;") == ">");
	CHECK(HtmlDecode("&amp;") == "&");

	CHECK(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M’s");
}