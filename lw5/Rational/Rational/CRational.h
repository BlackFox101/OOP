#pragma once

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational operator+() const;
	CRational operator-() const;

	CRational& operator+=(const CRational& right);
	CRational& operator-=(const CRational& right);
	CRational& operator*=(const CRational& right);
	CRational& operator/=(const CRational& right);

private:
	int m_numerator, m_denominator;

	void Normalize();
	void Reduce();

	int GetGCD(int a, int b);
};
CRational const operator+(const CRational& left, const CRational& right);
CRational const operator-(const CRational& left, const CRational& right);
CRational const operator*(const CRational& left, const CRational& right);
CRational const operator/(const CRational& left, const CRational& right);

bool operator==(const CRational& left, const CRational& right);
bool operator!=(const CRational& left, const CRational& right);
bool operator<(const CRational& left, const CRational& right);
bool operator<=(const CRational& left, const CRational& right);
bool operator>(const CRational& left, const CRational& right);
bool operator>=(const CRational& left, const CRational& right);

std::ostream& operator<<(std::ostream& stream, const CRational& number);
std::istream& operator>>(std::istream& stream, CRational& number);