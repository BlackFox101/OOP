#pragma once
#include <iosfwd>

std::string StringReplacer(std::string const& string, std::string searchString, std::string replaceString);

std::string HtmlDecode(std::string const& html);