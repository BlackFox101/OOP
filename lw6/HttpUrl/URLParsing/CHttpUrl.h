#pragma once
#include <iostream>
#include <string>

const unsigned short HTTP_PORT = 80;
const unsigned short HTTPS_PORT = 443;

const int PORT_MIN = 1;
const int PORT_MAX = USHRT_MAX;

class CHttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS
	};

	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

	std::string GetProtocolAsString() const;
private:
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;

	Protocol GetProtocolByString(const std::string& str) const;
	unsigned short GetPortByProtocol() const;
};

unsigned short GetPortByString(const std::string& str);

