#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../UrlParser/ParseUrl.h"

SCENARIO("getPort")
{
	Protocol protocol = Protocol::HTTP;
	CHECK(getPort(protocol) == 80);

	protocol = Protocol::HTTPS;
	CHECK(getPort(protocol) == 443);

	protocol = Protocol::FTP;
	CHECK(getPort(protocol) == 21);

	protocol = Protocol::NOT_DEFINED;
	CHECK(getPort(protocol) == -1);
}

SCENARIO("getProtocol")
{
	CHECK(getProtocol("http") == Protocol::HTTP);

	CHECK(getProtocol("https") == Protocol::HTTPS);

	CHECK(getProtocol("ftp") == Protocol::FTP);

	CHECK(getProtocol("ftasfsafp") == Protocol::NOT_DEFINED);
}

SCENARIO("ParseURL and output")
{
	std::string url = "http://www.mysite.com:24/docs/document1.html?page=30&lang=en#title";
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	REQUIRE(ParseURL(url, protocol, port, host, document));

	std::ostringstream output;
	OuputUrlParse(output, url, port, host, document);

	REQUIRE(output.str() == url +"\nHOST: www.mysite.com\nPORT: 24\nDOC: docs/document1.html?page=30&lang=en#title\n");
}