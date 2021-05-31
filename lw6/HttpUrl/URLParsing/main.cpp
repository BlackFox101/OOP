// URLParsing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "./CHttpUrl.h"

int main()
{
    while (!std::cin.eof())
    {
		std::cout << "Enter the url:\n";
		try
		{
			std::string str;
			std::cin >> str;
			std::cout << "\n";
			CHttpUrl url = str;

			std::cout << "URL: '" << url.GetURL() << "'\n";
			std::cout << "Protocol: '" << url.GetProtocolAsString() << "'\n";
			std::cout << "Domain: '" << url.GetDomain() << "'\n";
			std::cout << "Port: '" << url.GetPort() << "'\n";
			std::cout << "Document: '" << url.GetDocument() << "'\n\n";
		}
		catch (const std::exception& e)
		{
			if (!std::cin.eof())
			{
				std::cout << "Error: " << e.what() << "\n";
			}
		}
    }
}
