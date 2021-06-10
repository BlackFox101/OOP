#include "CMyString.h"
#include <stdexcept>
#include <iostream>

using namespace std;

CMyString::CMyString()
	: m_length(0)
{
	m_pString = new char[m_length + 1];
	m_pString[m_length] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
{
	m_pString = new char[m_length + 1];
	memcpy(m_pString, pString, m_length + 1);
	m_pString[m_length] = '\0';
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_pString, other.m_length)
{}

CMyString::CMyString(CMyString&& other) noexcept
	: m_length(other.m_length)
	, m_pString(other.m_pString)
{
	other.m_length = 0;
	other.m_pString = nullptr;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{}

CMyString::~CMyString()
{
	delete[] m_pString;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (length > m_length)
	{
		throw out_of_range("Length out of range");
	}
	if (start > length)
	{
		throw out_of_range("The beginning of the line is further away than the end of the line");
	}

	char* tempStr = new char[length - start + 1];
	size_t j = 0;
	for (size_t i = start; i < length; i++)
	{
		tempStr[j] = m_pString[i];
		j++;
	}
	tempStr[j] = '\0';

	return CMyString(tempStr);
}

void CMyString::Clear()
{
	m_length = 0;
}

const char* CMyString::GetStringData() const
{
	return m_pString;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (&other != this)
	{
		CMyString temp(other);
		swap(m_pString, temp.m_pString);
		swap(m_length, temp.m_length);
	}

	return *this;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	CMyString tempString;
	size_t newLength = m_length + other.m_length;

	tempString.m_length = newLength;
	tempString.m_pString = new char[newLength + 1];

	size_t i = 0;
	for (; i < m_length; i++)
	{
		tempString[i] = m_pString[i];
	}
	for (size_t j = 0; j < other.m_length && i < newLength; i++, j++)
	{
		tempString[i] = other.m_pString[j];
	}

	swap(tempString.m_pString, m_pString);
	swap(tempString.m_length, m_length);

	m_pString[newLength] = '\0';

	return *this;
}

CMyString operator+(const CMyString& left, const CMyString& right)
{
	size_t newLength = left.GetLength() + right.GetLength();

	CMyString tempString;
	tempString.m_length = newLength;
	tempString.m_pString = new char[newLength + 1];
	size_t i = 0;
	for (; i < left.m_length; i++)
	{
		tempString[i] = left.m_pString[i];
	}
	for (size_t j = 0; j < right.m_length && i < newLength; i++, j++)
	{
		tempString[i] = right.m_pString[j];
	}
	tempString.m_pString[newLength] = '\0';

	return tempString;
}

bool operator==(const CMyString& left, const CMyString& right)
{
	if (left.GetLength() != right.GetLength())
	{
		return false;
	}

	const char* leftStr = left.GetStringData();
	const char* rightStr = right.GetStringData();
	size_t minLength = min(left.GetLength(), right.GetLength());

	int res = memcmp(leftStr, rightStr, minLength);

	return res == 0;
}
bool operator!=(const CMyString& left, const CMyString& right)
{
	return !(left == right);
}

bool operator<(const CMyString& left, const CMyString& right)
{
	const char* leftStr = left.GetStringData();
	const char* rightStr = right.GetStringData();

	size_t minLength = min(left.GetLength(), right.GetLength());

	int res = memcmp(leftStr, rightStr, minLength);

	return res < 0 || (left.GetLength() < right.GetLength() &&  res == 0);
}
bool operator>(const CMyString& left, const CMyString& right)
{
	return right < left && left != right;
}

bool operator<=(const CMyString& left, const CMyString& right)
{
	return (left < right || left == right);
}
bool operator>=(const CMyString& left, const CMyString& right)
{
	return (left > right || left == right);
}

const char& CMyString::operator[](size_t index) const
{
	if (index > m_length)
	{
		throw out_of_range("Index out of range");
	}

	return m_pString[index];
}
char& CMyString::operator[](size_t index)
{
	if (index > m_length)
	{
		throw out_of_range("Index out of range");
	}

	return m_pString[index];
}

ostream& operator<<(ostream& stream, const CMyString& str)
{
	stream << str.GetStringData();

	return stream;
}
istream& operator>>(istream& stream, CMyString& str)
{
	char ch;
	while (stream.get(ch) && ch != '\n')
	{
		str += string(1, ch);
	}

	return stream;
}