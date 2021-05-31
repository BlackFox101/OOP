#include <iostream>
#include "CRational.h"
#include <stdexcept>

using namespace std;

// Designers

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
	{
		throw invalid_argument("The denominator cannot be zero!");
	}

	Normalize();
}

// Public

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return (double)m_numerator / m_denominator;
}

pair<int, CRational> CRational::ToCompoundFraction() const
{
	int wholePart = m_numerator / m_denominator;
	int remains = m_numerator % m_denominator;

	return { wholePart, CRational(remains, m_denominator) };
}

// Private

void CRational::Normalize()
{
	bool isNegative = (m_numerator < 0 && m_denominator > 0) || (m_numerator > 0 && m_denominator < 0);
	int tempNumerator = abs(m_numerator);
	int tempDenominator = abs(m_denominator);

	if (isNegative)
	{
		tempNumerator *= -1;
	}

	m_numerator = tempNumerator;
	m_denominator = tempDenominator;

	Reduce();
}

void CRational::Reduce()
{
	int gcd = GetGCD(m_numerator, m_denominator);

	m_numerator /= gcd;
	m_denominator /= gcd;
}

int CRational::GetGCD(int a, int b)
{
	while (b)
	{
		int tempA = a % b;
		a = b;
		b = tempA;
	}

	return abs(a);
}

// Public

CRational CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}
CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator+=(const CRational& right)
{
	m_numerator = m_numerator * right.GetDenominator() + right.GetNumerator() * m_denominator;
	m_denominator = m_denominator * right.GetDenominator();

	Reduce();

	return *this;
}
CRational& CRational::operator-=(const CRational& right)
{
	m_numerator = m_numerator * right.GetDenominator() - right.GetNumerator() * m_denominator;
	m_denominator = m_denominator * right.GetDenominator();

	Reduce();

	return *this;
}
CRational& CRational::operator*=(const CRational& right)
{
	m_numerator = m_numerator * right.GetNumerator();
	m_denominator = m_denominator * right.GetDenominator();

	Reduce();

	return *this;
}
CRational& CRational::operator/=(const CRational& right)
{
	int tempDenominator = m_denominator * right.GetNumerator();
	if (tempDenominator == 0)
	{
		throw invalid_argument("After multiplication, the denominator will be zero");
	}
	m_numerator = m_numerator * right.GetDenominator();
	m_denominator = tempDenominator;

	Normalize();

	return *this;
}

// ---------------------------------------------------

CRational const operator+(const CRational& left, const CRational& right)
{
	CRational temp = left;

	return temp += right;
}
CRational const operator-(const CRational& left, const CRational& right)
{
	CRational temp = left;

	return temp -= right;
}
CRational const operator*(const CRational& left, const CRational& right)
{
	CRational temp = left;

	return temp *= right;
}
CRational const operator/(const CRational& left, const CRational& right)
{
	CRational temp = left;

	return temp /= right;
}

bool operator==(const CRational& left, const CRational& right)
{
	return left.GetNumerator() == right.GetNumerator() && left.GetDenominator() == right.GetDenominator();
}
bool operator!=(const CRational& left, const CRational& right)
{
	return !(left == right);
}
bool operator<(const CRational& left, const CRational& right)
{
	CRational temp = left - right;

	return temp.GetNumerator() < 0;
}
bool operator<=(const CRational& left, const CRational& right)
{
	return (left < right || left == right);
}
bool operator>(const CRational& left, const CRational& right)
{
	return (!(left < right) && left != right);
}
bool operator>=(const CRational& left, const CRational& right)
{
	return (left > right || left == right);
}

ostream& operator<<(ostream& stream, const CRational& number)
{
	return stream << number.GetNumerator() << "/" << number.GetDenominator();
}
istream& operator>>(istream& stream, CRational& number)
{
	int numerator;
	int denominator;

	if ((stream >> numerator) && (stream.get() == '/') && (stream >> denominator))
	{
		number = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}