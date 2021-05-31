#include "Car.h"
#include <map>

using namespace std;

struct SpeedRange
{
	int min;
	int max;
};

map<int, SpeedRange> gearSpeed = {
	{-1, {0, 20}},
	{0, {0, 150}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}}
};

bool Car::IsTurnedOn() const
{
	return m_isTurnedOn;
}

Direction Car::GetDirection() const
{
	return m_direction;
}

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	if (!Car::IsTurnedOn())
	{
		m_isTurnedOn = true;
	}

	return m_isTurnedOn;
}

bool Car::TurnOffEngine()
{
	if (m_speed == 0 && m_gear == 0)
	{
		m_isTurnedOn = false;
		return true;
	}

	return false;
}

bool Car::SetGear(int gear) // [-1 .. 5]
{
	if (Car::CanSetGear(gear))
	{
		m_gear = gear;
		return true;
	}

	return false;
}

bool Car::SetSpeed(int speed)
{
	const int currentSpeed = m_speed;
	if (currentSpeed == speed)
	{
		return true;
	}

	if (Car::CanSetSpeed(speed))
	{
		m_speed = speed;

		if (m_gear == -1)
		{
			m_direction = Direction::Back;
		}
		if (m_gear >= 0 && speed > 0)
		{
			m_direction = Direction::Forward;
		}
		if (speed == 0)
		{
			m_direction = Direction::Stand;
		}
		return true;
	}

	return false;
}

bool Car::CanSetGear(int gear) const
{
	if (gear > MAX_GEAR || gear < MIN_GEAR)
	{
		return false;
	}

	if (Car::IsTurnedOn())
	{
		const int currentSpeed = m_speed;
		SpeedRange speedRange = gearSpeed[gear];
		if (currentSpeed < speedRange.min || currentSpeed > speedRange.max)
		{
			return false;
		}

		if (gear == -1)
		{
			return currentSpeed == 0;
		}

		const int currentGear = m_gear;
		if (gear == 1 && currentGear == -1)
		{
			return currentSpeed == 0;
		}

		if (gear == 1 && currentGear == 0)
		{
			const Direction dir = m_direction;
			return dir != Direction::Back;
		}

		return true;
	}
	else if(gear == 0)
	{
		return true;
	}

	return false;
}

bool Car::CanSetSpeed(int speed) const
{
	if (!Car::IsTurnedOn())
	{
		return false;
	}

	const int currentGear = m_gear;
	SpeedRange speedRange = gearSpeed[currentGear];
	if (speed < speedRange.min || speed > speedRange.max)
	{
		return false;
	}

	if (currentGear == 0)
	{
		const int currentSpeed = m_speed;
		if (speed > currentSpeed)
		{
			return false;
		}
	}

	return true;
}