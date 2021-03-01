#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <set>
#include <typeinfo>
#include "Radix.h"

using namespace std;

struct Args
{
    string sourceNotation;
    string destinationNotation;
    string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage Radix.exe <source notation> <destination notation> <value>\n";
        return std::nullopt;
    }
    Args args;
    args.sourceNotation = argv[1];
    args.destinationNotation = argv[2];
    args.value = argv[3];

    return args;
}

const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSRUVWXYZ";

// Перевод строки в число
int StringToInt(const string& str, bool& wasError)
{
    size_t pos;
    int number = stoi(str, &pos);
    if (pos != str.length())
    {
        wasError = true;
    }
    return number;
}

// Возведение в степень
// TODO: Проверка на переполненние
int RaiseDegree(const int& number, const int& degree)
{
    int degreeNumber = 1;
    for (int i = 0; i < degree; i++)
    {
        degreeNumber *= number;
    }

    return degreeNumber;
}

// Перевод в десятичную систему счисления
int ConvertToDecimalNotation(const string& value, int sourceNotation)
{
    int step = 0;
    int number = 0;
    for (int i = value.length() - 1; i >= 0  && value[i] != '-'; --i)
    {
        int digit = value[i] - '0';
        if (digit >= 10)
        {
            digit = CHARACTERS.find(value[i]);
        }
        if (value[0] == '-')
        {
            number -= digit * RaiseDegree(sourceNotation, step);
        }
        else
        {
            number += abs(digit) * RaiseDegree(sourceNotation, step);
        }
        step++;
    }

    return number;
}

void CalculationNumber(int& tempNumber, int destinationNotation, string& destinationNotationNumber)
{
    int remains;
    remains = tempNumber % destinationNotation;
    tempNumber = tempNumber / destinationNotation;
    destinationNotationNumber += CHARACTERS[abs(remains)];
}

// Перевод из десятичной системы в нужную
string ConvertToDestinationNotation(int& tempNumber, int destinationNotation)
{
    string destinationNotationNumber;
    if (tempNumber > 0)
    {
        do
        {
            CalculationNumber(tempNumber, destinationNotation, destinationNotationNumber);
        } while (tempNumber > destinationNotation);
    }
    else
    {
        do
        {
            CalculationNumber(tempNumber, destinationNotation, destinationNotationNumber);
        } while (tempNumber < 0);
    }

    return destinationNotationNumber;
}

// Перевод системы счисления
string ConvertNumberSystem(const string& value, const int sourceNotation, const int destinationNotation, bool& wasError)
{
    //Проверка если передана не верная система счисления
    if (!(2 <= sourceNotation && sourceNotation <= 36) || !(2 <= destinationNotation && destinationNotation <= 36))
    {
        cout << "One of the number systems does not exist\n";
        wasError = true;
        return value;
    }

    // Множество из символов начальной системы счисления
    set<char> charactersInSourceSystem = { '-' };
    for (int i = 0; i < sourceNotation; i++)
    {
        charactersInSourceSystem.insert(CHARACTERS[i]);
    }

    // Проверка переданное число соотвествует начальной системе счисления
    for (auto i : value)
    {
        if (charactersInSourceSystem.find(i) == charactersInSourceSystem.end())
        {
            cout << "The number of the wrong number system" << endl;
            wasError = true;
            return value;
        }
    }

    // Если нужная система совпадает с начальной
    if (sourceNotation == destinationNotation)
    {
        return value;
    }

    // Перевод в числа в привычную систему счисления(10)
    int number = 0;
    if (sourceNotation != 10)
    {
        number = ConvertToDecimalNotation(value, sourceNotation);
    }
    else
    {
        number = StringToInt(value, wasError);
    }

    if ((value != "-1" || value != "1") && (number == -1 || number == 1))
    {
        wasError = true;
        cout << "The number is very large" << endl;
        return value;
    }

    // Если нужна десятичная
    if (destinationNotation == 10)
    {
        return to_string(number);
    }

    // Перевод из десятичной системы в нужную
    int tempNumber = number;
    string destinationNotationNumber = ConvertToDestinationNotation(tempNumber, destinationNotation);
    if (number < 0)
    {
        destinationNotationNumber += "-";
    }
    else
    {
        destinationNotationNumber += CHARACTERS[tempNumber];
    }

    if (destinationNotationNumber == "1-")
    {
        wasError = true;
        cout << "The number is very large" << endl;
        return value;
    }

    string reverse;
    for (int i = destinationNotationNumber.length() - 1; i >= 0; --i)
    {
        reverse += (destinationNotationNumber[i]);
    }

    return reverse;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    // Проверка правильности аргументов командной строки
    if (!args)
    {
        return 1;
    }

    bool wasError = false;
    // Перевод начальной системы счисления из строки в число
    int sourceNotation = StringToInt(args->sourceNotation, wasError);
    if (wasError)
    {
        cout << "Not the number system passed: '" << args->sourceNotation << "'\n";
        return 1;
    }

    // Перевод следующей системы счисления из строки в число
    int destinationNotation = StringToInt(args->destinationNotation, wasError);
    if (wasError)
    {
        cout << "Not the number system passed: '" << args->destinationNotation << "'\n";
        return 1;
    }

    string number = ConvertNumberSystem(args->value, sourceNotation, destinationNotation, wasError);
    if (wasError)
    {
        return 1;
    }

    cout << number << endl;

    return 0;
}