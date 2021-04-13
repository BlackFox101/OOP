#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../UrlParser/ParseUrl.h"

SCENARIO("getPort")
{
	Protocol protocol = Protocol::HTTP;
	CHECK(GetPort(protocol) == 80);

	protocol = Protocol::HTTPS;
	CHECK(GetPort(protocol) == 443);

	protocol = Protocol::FTP;
	CHECK(GetPort(protocol) == 21);
}

SCENARIO("getProtocol")
{
	CHECK(GetProtocol("http") == Protocol::HTTP);

	CHECK(GetProtocol("https") == Protocol::HTTPS);

	CHECK(GetProtocol("ftp") == Protocol::FTP);
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

	REQUIRE(output.str() == url + "\n" + 
		"HOST: www.mysite.com\n"+
		"PORT: 24\n"+
		"DOC: docs/document1.html?page=30&lang=en#title\n");
}