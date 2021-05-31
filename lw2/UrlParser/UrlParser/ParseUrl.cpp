#include "ParseUrl.h"

using namespace std;

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	smatch result;
	regex regular("(([Hh][Tt][Tt][Pp][Ss]?|[Ff][Tt][Pp])"
		"(://)"
		"([\da-z\.-]+)"
		"(:[0-9]{0,})?"
		"(\/)"
		"(.+))");

	string stringPort;
	if (regex_match(url, result, regular))
	{
		protocol = GetProtocol(result[2]);
		host = result[4];
		stringPort = result[5];
		document = result[7];
	}
	else
	{
		return false;
	}

	if (empty(stringPort))
	{
		port = GetPort(protocol);
	}
	else
	{
		port = stoi(stringPort.substr(1, stringPort.length()));
	}

	return true;
}

Protocol GetProtocol(const string& protocol)
{
	string tempStr = protocol;
	transform(tempStr.begin(), tempStr.end(), tempStr.begin(), ::tolower);
	if (tempStr == "http")
	{
		return Protocol::HTTP;
	}
	if (tempStr == "https")
	{
		return Protocol::HTTPS;
	}
	if (tempStr == "ftp")
	{
		return Protocol::FTP;
	}
}

int GetPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	case Protocol::FTP:
		return 21;
	}
}

void OuputUrlParse(ostream& output, string const& url, const int port, const string& host, const string& document)
{
	output << url << endl;
	output << "HOST: " << host << endl;
	output << "PORT: " << port << endl;
	output << "DOC: " << document << endl;
}