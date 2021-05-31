#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../URLParsing/CHttpUrl.h"
#include "../URLParsing/CUrlParsingError.h"

using namespace std;

// TODO: протокол в любом регистре
// TODO: диапазон портов
// TODO: проверка чтобы порт по умолчанию не выводился

SCENARIO("Constructors")
{
	WHEN("Constructor from a string")
	{
		string url = "http://www.mysite.com:24/docs/document1.html?page=30&lang=en#title";

		try
		{
			CHttpUrl url(url);
			REQUIRE(true);
		}
		catch (const std::exception& e)
		{
			cout << e.what() << "\n";
			REQUIRE(false);
		}
	}

	WHEN("Constructor from parameters")
	{
		THEN("All arguments")
		{
			try
			{
				CHttpUrl url("www.mysite.com", "/docs/document1.html?page=30&lang=en#title", CHttpUrl::Protocol::HTTPS, 124);
				string str = "https://www.mysite.com:124/docs/document1.html?page=30&lang=en#title";

				CHECK(url.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
				CHECK(url.GetDomain() == "www.mysite.com");
				CHECK(url.GetPort() == 124);
				CHECK(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
				CHECK(url.GetURL() == str);
			}
			catch (const std::exception& e)
			{
				cout << e.what() << "\n";
				REQUIRE(false);
			}
		}

		THEN(" document == "" ")
		{
			try
			{
				CHttpUrl url("www.mysite.com", "", CHttpUrl::Protocol::HTTPS, 124);
				string str = "https://www.mysite.com:124/";

				CHECK(url.GetDocument() == "/");
				CHECK(url.GetDomain() == "www.mysite.com");
				CHECK(url.GetPort() == 124);
				CHECK(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
				CHECK(url.GetURL() == str);
			}
			catch (const std::exception& e)
			{
				cout << e.what() << "\n";
				REQUIRE(false);
			}
		}

		THEN(" Invalid domen")
		{
			try
			{
				CHttpUrl url("", "", CHttpUrl::Protocol::HTTPS, 124);
				CHECK(false);
			}
			catch (const std::exception& e)
			{
				CHECK(true);
			}
		}

		THEN(" Invalid domen")
		{
			try
			{
				CHttpUrl url("", "", CHttpUrl::Protocol::HTTPS, 124);
				CHECK(false);
			}
			catch (const std::exception& e)
			{
				CHECK(true);
			}
		}

		WHEN("Numeric domain")
		{
			try
			{
				CHttpUrl url("127.0.0.1", "", CHttpUrl::Protocol::HTTPS, 124);
				CHECK(true);
			}
			catch (const std::exception& e)
			{
				CHECK(false);
			}
		}
	}
	WHEN("Numeric domain")
	{
		string url = "http://127.0.0.1";

		try
		{
			CHttpUrl url(url);
			REQUIRE(true);
		}
		catch (const std::exception& e)
		{
			cout << e.what() << "\n";
			REQUIRE(false);
		}
	}
}

SCENARIO(" Geters ")
{

	try
	{
		WHEN(" GetURL ")
		{
			string str = "http://www.mysite.com:24/docs/document1.html?page=30&lang=en#title";
			CHttpUrl url(str);
			REQUIRE(url.GetURL() == "http://www.mysite.com:24/docs/document1.html?page=30&lang=en#title");
		}
		WHEN(" GetDomain ")
		{
			string str = "http://www.mysite.com:24/docs/document1.html?page=30&lang=en#title";
			CHttpUrl url(str);
			REQUIRE(url.GetDomain() == "www.mysite.com");
		}
		WHEN(" GetProtocol ")
		{
			string str = "http://www.mysite.com:24/docs/document1.html?page=30&lang=en#title";
			CHttpUrl url(str);
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);

			str = "https://www.mysite.com:24/docs/document1.html?page=30&lang=en#title";
			url = str;
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);

			str = "ftp://www.mysite.com:24/docs/document1.html?page=30&lang=en#title";
			try
			{
				url = str;
				REQUIRE(false);
			}
			catch (const std::exception&)
			{
				REQUIRE(true);
			}
		}
		WHEN(" GetPort ")
		{
			string str = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
			CHttpUrl url(str);
			CHECK(url.GetPort() == 80);

			str = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
			url = str;
			CHECK(url.GetPort() == 443);

			str = "https://www.mysite.com:24/docs/document1.html?page=30&lang=en#title";
			url =str;
			CHECK(url.GetPort() == 24);

			str = "https://www.mysite.com:" + PORT_MAX+1;
			try
			{
				url = str;
				REQUIRE(false);
			}
			catch (const std::exception&)
			{
				REQUIRE(true);
			}

			str = "https://www.mysite.com:0";
			try
			{
				url = str;
				REQUIRE(false);
			}
			catch (const std::exception&)
			{
				REQUIRE(true);
			}

			str = "https://www.mysite.com:-123";
			try
			{
				url = str;
				REQUIRE(false);
			}
			catch (const std::exception&)
			{
				REQUIRE(true);
			}

			str = "https://www.mysite.com:";
			try
			{
				url = str;
				REQUIRE(false);
			}
			catch (const std::exception&)
			{
				REQUIRE(true);
			}
		}
		WHEN(" GetDocument ")
		{
			string str = "http://www.mysite.com";
			CHttpUrl url(str);
			REQUIRE(url.GetDocument() == "/");

			str = "https://www.mysite.com:24";
			url = str;
			CHECK(url.GetDocument() == "/");

			str = "https://www.mysite.com:24/docs/document1.html?page=30&lang=en#title";
			url = str;
			CHECK(url.GetDocument() == "/docs/document1.html?page=30&lang=en#title");

			str = "https://www.mysite.com:24";
			url = str;
			CHECK(url.GetDocument() == "/");

			str = "https://www.mysite.com:24/";
			url = str;
			CHECK(url.GetDocument() == "/");
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
		REQUIRE(false);
	}
}

SCENARIO("Protocol in any register")
{
	try
	{
		string str = "HTTP://www.mysite.com";
		CHttpUrl url(str);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
		REQUIRE(false);
	}

	try
	{
		string str = "HtTpS://www.mysite.com";
		CHttpUrl url(str);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
		REQUIRE(false);
	}
}

SCENARIO("Port range")
{
	WHEN("Constructor from a string")
	{
		try
		{
			string str = "HTTP://www.mysite.com:0";
			CHttpUrl url(str);
			CHECK(false);
		}
		catch (const std::exception& e)
		{
			CHECK(true);
		}

		try
		{
			string str = "HtTpS://www.mysite.com:1";
			CHttpUrl url(str);
			CHECK(true);
		}
		catch (const std::exception& e)
		{
			CHECK(false);
		}

		try
		{
			string str = "HtTpS://www.mysite.com:65535";
			CHttpUrl url(str);
			CHECK(true);
		}
		catch (const std::exception& e)
		{
			CHECK(false);
		}

		try
		{
			string str = "HtTpS://www.mysite.com:65536";
			CHttpUrl url(str);
			CHECK(false);
		}
		catch (const std::exception& e)
		{
			CHECK(true);
		}
	}

	WHEN("Constructor from parameters")
	{
		try
		{
			CHttpUrl url("www.mysite.com", "", CHttpUrl::Protocol::HTTPS, 0);
			CHECK(false);
		}
		catch (const std::exception&)
		{
			CHECK(true);
		}
		try
		{
			CHttpUrl url("www.mysite.com", "", CHttpUrl::Protocol::HTTPS, 1);
			CHECK(true);
		}
		catch (const std::exception&)
		{
			CHECK(false);
		}
		try
		{
			CHttpUrl url("www.mysite.com", "", CHttpUrl::Protocol::HTTPS, 65535);
			CHECK(true);
		}
		catch (const std::exception&)
		{
			CHECK(false);
		}
		try
		{
			CHttpUrl url("www.mysite.com", "", CHttpUrl::Protocol::HTTPS, 65536);
			CHECK(false);
		}
		catch (const std::exception&)
		{
			CHECK(true);
		}
	}
}

SCENARIO("Do not output the default port")
{
	WHEN("http")
	{
		string str = "http://www.mysite.com:80";
		CHttpUrl url(str);
		CHECK(url.GetURL() == "http://www.mysite.com/");

		str = "http://www.mysite.com:445";
		CHttpUrl url2(str);
		CHECK(url2.GetURL() == "http://www.mysite.com:445/");
	}
	WHEN("https")
	{
		string str = "https://www.mysite.com:443";
		CHttpUrl url(str);
		CHECK(url.GetURL() == "https://www.mysite.com/");

		str = "https://www.mysite.com:445";
		CHttpUrl url2(str);
		CHECK(url2.GetURL() == "https://www.mysite.com:445/");
	}
}