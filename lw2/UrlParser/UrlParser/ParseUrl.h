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
	FTP,
	NOT_DEFINED
};

int getPort(Protocol protocol);

Protocol getProtocol(const string& protocol);

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document);

void OuputUrlParse(ostream& output, string const& url, int port, const string& host, const string& document);