#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Car/Car.h"
#include "../Car/CarControl.h"

using namespace std;

SCENARIO("Start and stop the engine")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.TurnOnEngine());
	CHECK(car.IsTurnedOn() == true);

	REQUIRE(car.TurnOffEngine());
	CHECK(car.IsTurnedOn() == false);

	CHECK(car.GetDirection() == Direction::Stand);
}

SCENARIO("canSetGear")
{
	WHEN("Check the gear range")
	{
		Car car;

		CHECK(car.CanSetGear(-2) == false);
		CHECK(car.CanSetGear(6) == false);
		CHECK(car.CanSetGear(-1) == false);
		CHECK(car.CanSetGear(0) == true);
		CHECK(car.CanSetGear(5) == false);
		car.TurnOnEngine();
	}

	WHEN("Engine running")
	{
		Car car;
		car.TurnOnEngine();
		CHECK(car.CanSetGear(-1) == true);
		CHECK(car.CanSetGear(1) == true);
		// Переключится не входя в диапазон скоростей
		CHECK(car.CanSetGear(2) == false);
	}
}

SCENARIO("SetGear")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	CHECK(car.GetGear() == 1);

	REQUIRE(car.SetGear(-1));
	CHECK(car.GetGear() == -1);
}

SCENARIO("canSetSpeed")
{
	Car car;

	// Двигатель выключен
	CHECK(car.CanSetSpeed(20) == false);
	CHECK(car.CanSetSpeed(10) == false);

	car.TurnOnEngine();
	// нейтралка, скорость 0
	CHECK(car.CanSetSpeed(0) == true);
	CHECK(car.CanSetSpeed(20) == false);
	CHECK(car.CanSetSpeed(30) == false);

	REQUIRE(car.SetGear(1));
	CHECK(car.GetGear() == 1);
	CHECK(car.CanSetSpeed(20) == true);
	CHECK(car.CanSetSpeed(30) == true);
}

SCENARIO("setSpeed")
{
	Car car;

	// Двигатель выключен
	CHECK(car.CanSetSpeed(20) == false);
	CHECK(car.CanSetSpeed(10) == false);

	REQUIRE(car.TurnOnEngine());
	CHECK(car.IsTurnedOn() == true);
	// нейтралка, скорость 0
	CHECK(car.SetSpeed(0) == true);
	CHECK(car.SetSpeed(20) == false);
	CHECK(car.SetSpeed(30) == false);

	REQUIRE(car.SetGear(1));
	CHECK(car.GetGear() == 1);
	CHECK(car.SetSpeed(20) == true);
	CHECK(car.GetSpeed() == 20);
	CHECK(car.SetSpeed(30) == true);
	CHECK(car.GetSpeed() == 30);

	REQUIRE(car.SetGear(2));
	CHECK(car.SetSpeed(50) == true);
	CHECK(car.GetSpeed() == 50);

	REQUIRE(car.SetGear(3));
	CHECK(car.GetGear() == 3);
}

SCENARIO("Switching from rear to first gear")
{
	Car car;

	REQUIRE(car.TurnOnEngine());
	CHECK(car.IsTurnedOn() == true);
	REQUIRE(car.SetGear(-1));
	CHECK(car.GetGear() == -1);
	car.SetSpeed(1);
	REQUIRE(car.SetGear(1) == false);
	CHECK(car.GetGear() == -1);
}