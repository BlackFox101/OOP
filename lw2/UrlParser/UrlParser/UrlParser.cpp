#include <iostream>
#include "ParseUrl.h"

int main()
{
	std::string url;
	cin >> url;
	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	if (ParseURL(url, protocol, port, host, document))
	{
		OuputUrlParse(cout, url, port, host, document);
	}
	else
	{
		cout << "Invalid URL\n";
	}

	return 0;
}