#include "pch.h"
#include "CHttpUrl.h"

using namespace std;

CHttpUrl::CHttpUrl(string const& url)
{
	regex ex("([^\w]*)://([^/ :]+)(/?[^ #?]*):([^/ ]*)");
	cmatch what;
	string protocol, domain, document, port;

	if (regex_match(url.c_str(), what, ex))
	{
		protocol = string(what[1].first, what[1].second);
		domain = string(what[2].first, what[2].second);
		document = string(what[3].first, what[3].second);
		port = string(what[4].first, what[4].second);

		if (document.empty() || domain.empty())
		{
			throw invalid_argument("ERROR: wrong url\nURL must consist of protocol://domain/dodumen:port (port optional)\n");
		}

		m_protocol = StringToProtocol(protocol);
		m_domain = domain;
		m_document = document;

		try
		{
			m_port = static_cast<unsigned short>(strtoul(port.c_str(), NULL, 0));
		}
		catch (invalid_argument const e)
		{
			throw invalid_argument(e);
		}
	}
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol)
	: m_domain(domain)
	, m_document(document)
	, m_protocol(protocol)
	, m_port(0)
{
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol, unsigned short port)
	: m_domain(domain)
	, m_document(document)
	, m_protocol(protocol)
	, m_port(port)
{
}

string CHttpUrl::GetUrl() const
{
	string protocol = "http";
	string url;

	if (m_protocol == Protocol::HTTPS)
	{
		protocol = "https";
	}

	if (m_port != 0)
	{
		url = protocol + "://" + m_domain + m_document + ":" + to_string(m_port);
	}
	else
	{
		url = protocol + "://" + m_domain + m_document;
	}

	return url;
}

string CHttpUrl::GetDomain() const
{
	return m_domain;
}

string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol()
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void ToLowercase(string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

Protocol StringToProtocol(string& inpString)
{
	ToLowercase(inpString);

	if (inpString == "https")
	{
		return Protocol::HTTPS;
	}
	else if (inpString == "http")
	{
		return Protocol::HTTP;
	}
	else
	{
		throw invalid_argument("ERROR: wrong protocol value\nProtocol must be http or https\n");
	}
}
