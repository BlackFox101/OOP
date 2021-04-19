#pragma once
#include <iostream>

const int MIN_SPEED = 0;
const int MAX_SPEED = 150;
const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

enum class Direction
{
	Forward,
	Stand,
	Back
};

class Car
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

	bool CanSetGear(int gear) const;
	bool CanSetSpeed(int speed) const;

private:
	bool m_isTurnedOn = false; // включен или выключен
	Direction m_direction = Direction::Stand; // вперед, назад или стоим на месте
	int m_speed = 0; // скорость
	int m_gear = 0; // текущая передача
};