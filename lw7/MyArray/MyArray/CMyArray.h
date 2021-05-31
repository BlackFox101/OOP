#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class CMyArray
{
public:
	CMyArray()
		: m_size(0)
		, m_pArray(nullptr)
	{}
	CMyArray(size_t size)
		: m_size(size)
	{
		m_pArray = new T[m_size];
	}
	CMyArray(size_t size, const T& value)
		: m_size(size)
	{
		m_pArray = new T[m_size];
		for (size_t i = 0; i < m_size; i++)
		{
			m_pArray[i] = value;
		}
	}
	CMyArray(const CMyArray<T>& other)
	{
		m_pArray = new T[other.m_size];
		memcpy(m_pArray, other.m_pArray, other.m_size);
		m_size = other.m_size;
	}
	CMyArray(CMyArray<T>&& other) noexcept
		: m_size(other.m_size)
		, m_pArray(other.m_pArray)
	{
		other.m_size = 0;
		other.m_pArray = nullptr;
	}
	~CMyArray() noexcept
	{
		delete[] m_pArray;
	}

	size_t GetSize() const
	{
		return m_size;
	}
	void Resize(size_t size)
	{
		if (size < m_size)
		{
			m_size = size;
		}
		else if (size > m_size)
		{
			T* temp = new T[size];
			for (size_t i = 0; i < m_size; i++)
			{
				temp[i] = m_pArray[i];
			}
			for (size_t i = m_size; i < size; i++)
			{
				temp[i] = DefaultValue();
			}
			delete[] m_pArray;

			m_pArray = temp;
			m_size = size;
		}
	}
	void PushBack(const T& value)
	{
		T* temp = new T[m_size + 1];

		for (size_t i = 0; i < m_size; i++)
		{
			temp[i] = m_pArray[i];
		}
		temp[m_size] = value;
		delete[] m_pArray;

		m_pArray = temp;
		m_size++;
	}
	void Clear()
	{
		delete[] m_pArray;
		m_pArray = nullptr;
		m_size = 0;
	}

	CMyArray<T>& operator=(const CMyArray<T>& other)
	{
		if (this == &other)
			return *this;

		T* temp = new T[other.m_size];
		delete[] m_pArray;
		m_size = other.m_size;
		m_pArray = temp;
		
		return *this;
	}
	CMyArray<T>& operator=(CMyArray<T>&& other) noexcept
	{
		if (this == &other)
			return *this;

		m_pArray = other.m_pArray;
		m_size = other.m_size;
		other.m_pArray = nullptr;
		other.m_size = 0;

		return *this;
	}

	const T& operator[](size_t index) const
	{
		if (index > m_size)
		{
			throw out_of_range("Index out of range");
		}

		return m_pArray[index];
	}
	T& operator[](size_t index)
	{
		if (index > m_size)
		{
			throw out_of_range("Index out of range");
		}

		return m_pArray[index];
	}

	//friend class Iterator<T>;
	//typedef class Iterator<T> iterator;

	/*Iterator<T>begin();
	Iterator<T>();

	Iterator<T>rbegin();
	Iterator<T>rend();*/

private:
	T* m_pArray;
	size_t m_size;

	T DefaultValue()
	{
		if (typeid(T) == typeid(int) || typeid(T) == typeid(double) || typeid(T) == typeid(float))
		{
			return 0;
		}
		if (typeid(T) == typeid(string))
		{
			return (T)"default";
		}
	}
};