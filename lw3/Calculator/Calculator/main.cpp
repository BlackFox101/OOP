#include <iostream>
#include "Calculator.h"

#include <cmath>
#include <regex>


int main()
{
    Calculator calc(cin, cout);
    while (!cin.eof())
    {
        optional<Command> command = calc.GetCommand();

        if (!command)
        {
            if (!cin.eof())
            {
                cout << "Command not found\n";
            }
            continue;
        }

        if (!calc.PerformCommand(*command))
        {
            cout << "Invalid command format\n";
        }
    }
}