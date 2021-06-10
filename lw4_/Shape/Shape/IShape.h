#pragma once
#include <string>

class IShape
{
	// TODO:
	// Виртуальный деструктор
	// shared_pointer передавать по ссылке
	// Навазние PushShape переименовать
public:
	virtual ~IShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
};