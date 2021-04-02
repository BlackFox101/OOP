#include <iostream>
#include <string>
#include <map>

using namespace std;

void HtmlEntityToChar(string& str, const string& htmlEntity)
{
	map<string, char> dictionary = {
		{"&quot;", '\"'},
		{"&apos;", '’'},
		{"&lt;", '<'},
		{"&gt;", '>'},
		{"&amp;", '&'}
	};

	if (dictionary.find(htmlEntity) != dictionary.end())
	{
		str.push_back(dictionary[htmlEntity]);
	}
	else
	{
		str.append(htmlEntity);
	}
}

string HtmlDecode(string const& html)
{
	string str;
	string htmlEntity;
	bool find = false;

	for (char ch : html)
	{
		if (ch == '&')
		{
			if (find)
			{
				str.append(htmlEntity);
				htmlEntity = "";
			}
			find = true;
		}

		if (find)
		{
			htmlEntity.push_back(ch);
		}
		else 
		{
			str.push_back(ch);
		}

		if (find && ch == ';')
		{
			HtmlEntityToChar(str, htmlEntity);
			htmlEntity = "";
			find = false;
		}
	}

	return str;
}

void HtmlDecodeLines(istream& input, ostream& output)
{
	string line;
	while (getline(input, line))
	{
		output << HtmlDecode(line);
		if (input.good())
		{
			output << "\n";
		}
	}
}