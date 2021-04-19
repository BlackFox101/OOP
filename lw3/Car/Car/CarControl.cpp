#include "CarControl.h"
#include "Car.h"
#include <algorithm>
#include <string>

using namespace std;

CarControl::CarControl(Car& car, ostream& output) : m_car(car), m_output(output)
{}

ostream& operator<<(ostream& stream, Direction const& dir)
{
	switch (dir)
	{
	case Direction::Back:
		stream << "Back";
		break;
	case Direction::Forward:
		stream << "Forward";
		break;
	case Direction::Stand:
		stream << "Stand";
		break;
	}
	return stream;
}

void CarControl::Info() const
{
	m_output << "Car info:\n";
	m_output << "Engine: " << (m_car.IsTurnedOn() ? "Yes" : "No") << endl;
	m_output << "Direction: " << m_car.GetDirection() << endl;
	m_output << "Speed: " << m_car.GetSpeed() << endl;
	m_output << "Gear: " << m_car.GetGear() << endl;
}

bool CarControl::EngineOn()
{
	if (m_car.IsTurnedOn())
	{
		m_output << "Engine was started\n";
		return true;
	}

	m_output << "Engine started\n";
	return m_car.TurnOnEngine();
}

bool CarControl::EngineOff()
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine shut down\n";
		return true;
	}

	m_output << "To turn off the car, there must be a neutral gear, and speed = 0\n";
	return false;
}

bool CarControl::SetGear(int gear)
{
	if (m_car.SetGear(gear))
	{
		m_output << "Gear switched successfully\n";
		return true;
	}

	m_output << "You can't change the gear to this one!\n";

	return false;
}

bool CarControl::SetSpeed(int speed)
{
	if (m_car.SetSpeed(speed))
	{
		m_output << "Speed changed successfully\n";
		return true;
	}

	m_output << "You can't change the speed to this oned!\n";

	return false;
}

Commands GetCommand(const string& str)
{
	string command = str;
	transform(command.begin(), command.end(), command.begin(), ::tolower);

	if (command == "info")
	{
		return Commands::Info;
	}
	else if (command == "engineon")
	{
		return Commands::EngineOn;
	}
	else if (command == "engineoff")
	{
		return Commands::EngineOff;
	}
	else if (command == "setgear")
	{
		return Commands::SetGear;
	}
	else if (command == "setspeed")
	{
		return Commands::SetSpeed;
	}
	else if (command == "exit")
	{
		return Commands::Exit;
	}
	else
	{
		return Commands::Unknown;
	}
}

bool CarControl::RunÑommand(Commands command, int value)
{
	switch (command)
	{
	case Commands::Info:
		CarControl::Info();
		return true;
	case Commands::EngineOn:
		CarControl::EngineOn();
		return true;
	case Commands::EngineOff:
		CarControl::EngineOff();
		return true;
	case Commands::SetGear:
		CarControl::SetGear(value);
		return true;
	case Commands::SetSpeed:
		CarControl::SetSpeed(value);
		return true;
	default:
		return false;
	}
}

bool StringToInt(const string& str, int& number)
{
	size_t pos;
	try
	{
		number = stoi(str, &pos);
		if (pos != str.length())
		{
			cout << "It's not a number\n";
			return false;
		}
	}
	catch (const out_of_range&)
	{
		cout << "The number is out of range(int)\n";
		return false;
	}

	return true;
}

optional<CommandData> GetCommandData()
{
	CommandData data;
	string str;
	cin >> str;
	data.command = GetCommand(str);
	if (data.command == Commands::SetGear || data.command == Commands::SetSpeed)
	{
		cin >> str;
		StringToInt(str, data.value);
	}

	return data;
}