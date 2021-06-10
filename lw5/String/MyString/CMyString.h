#pragma once
#include <string>

using namespace std;

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);

	~CMyString();

	size_t GetLength()const;
	const char* GetStringData()const;
	CMyString SubString(size_t start, size_t length)const;
	void Clear();

	CMyString& operator=(const CMyString& other);
	CMyString& operator+=(const CMyString& other);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	friend  CMyString operator+(const CMyString& left, const CMyString& right);

private:

	char* m_pString;
	size_t m_length;
};

CMyString operator+(const CMyString& left, const CMyString& right);

bool operator==(const CMyString& left, const CMyString& right);
bool operator!=(const CMyString& left, const CMyString& right);
bool operator<(const CMyString& left, const CMyString& right);
bool operator<=(const CMyString& left, const CMyString& right);
bool operator>(const CMyString& left, const CMyString& right);
bool operator>=(const CMyString& left, const CMyString& right);

std::ostream& operator<<(std::ostream& stream, const CMyString& str);
std::istream& operator>>(std::istream& stream, CMyString& str);