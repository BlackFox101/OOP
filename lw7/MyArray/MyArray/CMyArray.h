#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// TODO: memcpy нельзя
// утечки памяти
// Вместимость
// добавить тест push back array.push_back(array[i]);
// Проверить массив с длинныи строками

template <typename T>
class CMyArray
{

	template <bool IsConst>
	class CIterator
	{
		friend class CIterator<true>;
	public:
		using Iterator = CIterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using difference_type = ptrdiff_t;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		CIterator() = default;
		CIterator(const CIterator<false>& other)
			: m_item(other.m_item)
		{}

		reference& operator*() const
		{
			return *m_item;
		}

		Iterator& operator+=(difference_type offset)
		{
			m_item += offset;
			return *this;
		}
		Iterator& operator-=(difference_type offset)
		{
			m_item -= offset;
			return *this;
		}

		Iterator operator+(difference_type offset)
		{
			Iterator temp(m_item);
			return temp += offset;
		}
		Iterator operator-(difference_type offset)
		{
			Iterator temp(m_item);
			return temp -= offset;
		}

		Iterator& operator++()
		{
			return *this+=1;
		}
		Iterator operator++(int)
		{
			return ++*this;
		}
		Iterator& operator--()
		{
			return *this-=1;
		}
		Iterator operator--(int)
		{
			return  --*this;
		}

		friend bool operator==(const Iterator& left, const Iterator& right)
		{
			return left.m_item == right.m_item;
		}
		friend bool operator!=(const Iterator& left, const Iterator& right)
		{
			return left.m_item != right.m_item;
		}

		friend Iterator operator+(difference_type offset, const Iterator& it)
		{
			return it + offset;
		}
		friend Iterator operator-(difference_type offset, const Iterator& it)
		{
			return it - offset;
		}

	public:
		CIterator(T* item)
			: m_item(item)
		{
		}

	protected:
		T* m_item = nullptr;
	};

public:
	CMyArray()
		: m_size(0)
		, m_pArray(nullptr)
	{}
	CMyArray(size_t size)
		: m_size(size)
	{
		m_pArray = new T[m_size];
		for (size_t i = 0; i < m_size; i++)
		{
			m_pArray[i] = T();
		}
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
				temp[i] = T();
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
		if (index >= m_size)
		{
			throw out_of_range("Index out of range");
		}

		return m_pArray[index];
	}
	T& operator[](size_t index)
	{
		if (index >= m_size)
		{
			throw out_of_range("Index out of range");
		}

		return m_pArray[index];
	}

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;
	using const_reverse_iterator = reverse_iterator<const_iterator>;
	using reverse_iterator = reverse_iterator<iterator>;

	iterator begin()
	{
		return m_pArray;
	}
	iterator end()
	{
		return m_pArray + m_size;
	}
	const_iterator begin()const
	{
		return m_pArray;
	}
	const_iterator end() const
	{
		return m_pArray + m_size;
	}

	reverse_iterator rbegin()
	{
		return make_reverse_iterator(end());
	}
	reverse_iterator rend()
	{
		return make_reverse_iterator(begin());
	}
	const_reverse_iterator rbegin() const
	{
		return make_reverse_iterator(end());
	}
	const_reverse_iterator rend() const
	{
		return make_reverse_iterator(begin());
	}

private:
	T* m_pArray;
	size_t m_size;
};
