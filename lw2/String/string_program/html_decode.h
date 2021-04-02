#pragma once
#include <iosfwd>

std::string HtmlDecode(std::string const& html);

void HtmlDecodeLines(std::istream& input, std::ostream& output);

void HtmlEntityToChar(std::string& str, const std::string& htmlEntity);