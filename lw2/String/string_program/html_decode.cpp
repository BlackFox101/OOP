#include <string>

std::string StringReplacer(std::string const& string, std::string searchString, std::string replaceString)
{
	if (searchString == "" || searchString == replaceString)
	{
		return string;
	}

	std::string str = string;

	size_t pos = str.find(searchString);
	while (pos != std::string::npos) {
		str.replace(pos, searchString.size(), replaceString);
		pos = str.find(searchString, pos);
	}

	return str;
}

std::string HtmlDecode(std::string const& html)
{
	std::string HtmlDecoded = html;

	HtmlDecoded = StringReplacer(HtmlDecoded, "&quot;", "\"");
	HtmlDecoded = StringReplacer(HtmlDecoded, "&apos;", "’");
	HtmlDecoded = StringReplacer(HtmlDecoded, "&lt;", "<");
	HtmlDecoded = StringReplacer(HtmlDecoded, "&gt;", ">");
	HtmlDecoded = StringReplacer(HtmlDecoded, "&amp;", "&");

	return HtmlDecoded;
}