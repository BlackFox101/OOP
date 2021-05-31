#include "CHttpUrl.h"

#include <regex>
#include <algorithm>
#include <stdexcept>

#include "CUrlParsingError.h"

using namespace std;

CHttpUrl::CHttpUrl(string const& url)
{
	// протокол://домен[:порт][/документ]
	smatch result;
	regex regular("(([Hh][Tt][Tt][Pp][Ss]?)"
		"(://)"
		"([A-Za-z0-9\-\.]+)"
		"(:[0-9]{0,})?"
		"(\/.{0,})?)");

	if (!regex_match(url, result, regular))
	{
		throw CUrlParsingError("Invalid url!");
	}

	m_protocol = GetProtocolByString(result[2].str());
	m_domain = result[4].str();
	m_port = result[5].str().empty() ? GetPortByProtocol() : GetPortByString(result[5].str());
	m_document = result[6].str().empty() ? "/" : result[6].str();
}

CHttpUrl::CHttpUrl(const string& domain, const string& document, Protocol protocol)
{
	regex domenReg("([A-Za-z0-9\-\.]+)");
	if (regex_match(domain, domenReg))
	{
		throw CUrlParsingError("Invalid domen!");
	}
	m_protocol = protocol;
	m_domain = domain;
	m_document = document[0] == '/' ? document : '/' + document;
	m_port = GetPortByProtocol();
}

CHttpUrl::CHttpUrl(const string& domain, const string& document, Protocol protocol, unsigned short port)
{
	if (domain == "")
	{
		throw CUrlParsingError("The domain cannot be empty");
	}
	if (port > PORT_MAX || port < PORT_MIN)
	{
		throw CUrlParsingError("Invalid port! Port out of range(" + to_string(PORT_MIN) + " <= " + to_string(PORT_MAX) + ")");
	}
	m_protocol = protocol;
	m_domain = domain;
	m_document = document[0] == '/' ? document : '/' + document;
	m_port = port;
	// TODO: проверка на валидность
	// TODO: не пройдет домен 127.0.0.1
}

CHttpUrl::Protocol CHttpUrl::GetProtocolByString(const string& str) const
{
	string protocol = str;
	transform(protocol.begin(), protocol.end(), protocol.begin(), ::tolower);

	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	if (protocol == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Not expected URL!");
}

unsigned short GetPortByString(const string& str)
{
	string port = str.substr(1, str.length());
	try
	{
		size_t pos;
		int result = stoi(port, &pos);
		if (result > PORT_MAX || result < PORT_MIN)
		{
			throw CUrlParsingError("Invalid port! Port out of range(" + to_string(PORT_MIN) + " <= " + to_string(PORT_MAX) + ")");
		}
		if (pos != port.length())
		{
			throw CUrlParsingError("Invalid port: " + str);
		}

		return result;
	}
	catch (const invalid_argument&)
	{
		throw CUrlParsingError("Invalid port: '" + str + "'");
	}
	catch (const out_of_range&)
	{
		throw CUrlParsingError("Invalid port! Port out of range(" + to_string(PORT_MIN) + " <= " + to_string(PORT_MAX) + ")");
	}
}

unsigned short CHttpUrl::GetPortByProtocol() const
{
	switch (m_protocol)
	{
	case CHttpUrl::Protocol::HTTP:
		return 80;
	case CHttpUrl::Protocol::HTTPS:
		return 443;
	}

	throw CUrlParsingError("Invalid protocol!");
}

string CHttpUrl::GetProtocolAsString() const
{
	switch (m_protocol)
	{
	case CHttpUrl::Protocol::HTTP:
		return "http";
	case CHttpUrl::Protocol::HTTPS:
		return "https";
	}

	throw CUrlParsingError("Unknown protocol!");
}

string CHttpUrl::GetURL() const
{
	if ((m_protocol == CHttpUrl::Protocol::HTTP && m_port == HTTP_PORT) || (m_protocol == CHttpUrl::Protocol::HTTPS && m_port == HTTPS_PORT))
	{
		return GetProtocolAsString() + "://" + m_domain + m_document;
	}

	return GetProtocolAsString() + "://" + m_domain + ':' + to_string(m_port) + m_document;
}

string CHttpUrl::GetDomain() const
{
	return m_domain;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

string CHttpUrl::GetDocument() const
{
	return m_document;
}