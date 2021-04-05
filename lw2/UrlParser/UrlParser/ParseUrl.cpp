#include "ParseUrl.h"

using namespace std;

struct URLArgs
{
	string protocol;
	string host;
	string port;
	string document;
};

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	URLArgs urlArgs;
	smatch result;
	regex regular("(([Hh][Tt][Tt][Pp][Ss]?|[Ff][Tt][Pp])"
		"(://)"
		"([\da-z\.-]+)"
		"(:[0-9]{1,5})?"
		"(\/)"
		"(.+))");

	if (regex_match(url, result, regular))
	{
		urlArgs.protocol = result[2];
		urlArgs.host = result[4];
		urlArgs.port = result[5];
		urlArgs.document = result[7];
	}
	else
	{
		return false;
	}

	port = stoi(urlArgs.port.substr(1, urlArgs.port.length()));
	protocol = getProtocol(urlArgs.protocol);
	if (empty(urlArgs.port))
	{
		port = getPort(protocol);
	}
	host = urlArgs.host;
	document = urlArgs.document;

	return true;
}

Protocol getProtocol(const string& protocol)
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
	return Protocol::NOT_DEFINED;
}

int getPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	case Protocol::FTP:
		return 21;
	default:
		return -1;
	}
}

void OuputUrlParse(ostream& output, string const& url, int port, const string& host, const string& document)
{
	output << url << endl;
	output << "HOST: " << host << endl;
	output << "PORT: " << port << endl;
	output << "DOC: " << document << endl;
}