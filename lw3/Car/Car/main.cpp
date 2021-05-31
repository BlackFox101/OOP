#include <iostream>
#include "Car.h"
#include "CarControl.h"
#include <string>

int main()
{
    Car car;
    CarControl control(car, std::cout);
    while (true)
    {
        auto commandData = GetCommandData();

        if (commandData->command == Commands::Exit)
        {
            break;
        }

        if (!control.Run—ommand(commandData))
        {
            cout << "Command not found\n";
        }
    }
}