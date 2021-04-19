#include <iostream>
#include "Car.h"
#include "CarControl.h"
#include <string>

int main()
{
    Car car;
    CarControl control(car, std::cout);
    string line;
    while (true)
    {
        auto commandData = GetCommandData();

        if (commandData->command == Commands::Exit)
        {
            break;
        }

        if (!control.RunÑommand(commandData->command, commandData->value))
        {
            cout << "Command not found\n";
        }
    }
}