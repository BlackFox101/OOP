#pragma once
#include <iostream>
#include "Car.h"
#include <optional>

using namespace std;

enum class Commands
{
	Info,
	EngineOn,
	EngineOff,
	SetGear,
	SetSpeed,
	Exit,
	Unknown
};

struct CommandData
{
	Commands command;
	int value;
};

Commands GetCommand(const string& command);
bool StringToInt(const string& str, int& number);
optional<CommandData> GetCommandData();

class CarControl
{
public:
	CarControl(Car& car, ostream& output);

	bool Run—ommand(optional<CommandData> data);

	bool EngineOn();
	bool EngineOff();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

	void Info() const;

private:
	Car& m_car;
	ostream& m_output;
};

