#include <string>
#include <iostream>
#include <regex>
#include <algorithm>
#pragma once

using namespace std;

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

int GetPort(Protocol protocol);

Protocol GetProtocol(const string& protocol);

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document);

void OuputUrlParse(ostream& output, string const& url, const int port, const string& host, const string& document);