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
void StringToInt(const string& str, int& radix, bool& wasError)
{
    size_t pos;
    radix = stoi(str, &pos);
    if (pos != str.length())
    {
        wasError = true;
    }
}

// Возведение в степень
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
void ConvertToDecimalNotation(std::string& value, int& decimalNumber, int& sourceNotation)
{
    int step = 0;
    for (int i = value.length() - 1; i >= 0; --i)
    {
        int number = value[i] - '0';
        if (number >= 10)
        {
            number = CHARACTERS.find(value[i]);
        }
        decimalNumber = decimalNumber + (number * RaiseDegree(sourceNotation, step));
        step++;
    }
}

void CalculationNumber(int& tempNumber, int destinationNotation, std::string& destinationNotationNumber)
{
    int remains;
    remains = tempNumber % destinationNotation;
    tempNumber = tempNumber / destinationNotation;
    destinationNotationNumber += CHARACTERS[abs(remains)];
}

// Перевод из десятичной системы в нужную
void ConvertToDestinationNotation(int& tempNumber, int destinationNotation, std::string& destinationNotationNumber)
{
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
}

// Вывести число
void OutputNumber(std::string& destinationNotationNumber)
{
    for (int i = destinationNotationNumber.length() - 1; i >= 0; --i)
    {
        cout << destinationNotationNumber[i];
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    // Проверка правильности аргументов командной строки
    if (!args)
    {
        return 1;
    }

    int sourceNotation = 0; // Начальная система счисления
    int destinationNotation = 0; // В какую перевести
    bool wasError = false;

    // Перевод начальной системы счисления из строки в число
    StringToInt(args->sourceNotation, sourceNotation, wasError);
    if (wasError)
    {
        cout << "Not the number system passed: '" << args->sourceNotation << "'\n";
        return 1;
    }

    // Перевод следующей системы счисления из строки в число
    StringToInt(args->destinationNotation, destinationNotation, wasError);
    if (wasError)
    {
        cout << "Not the number system passed: '" << args->destinationNotation << "'\n";
        return 1;
    }

    //Проверка если передана не верная система счисления
    if (!(2 <= sourceNotation && sourceNotation <= 36) || !(2 <= destinationNotation && destinationNotation <= 36))
    {
        cout << "One of the number systems does not exist\n";
        return 1;
    }

    // Множество из символов начальной системы счисления
    set<char> charactersInSourceSystem = {'-'};
    for (int i = 0; i < sourceNotation; i++)
    {
        charactersInSourceSystem.insert(CHARACTERS[i]);
    }

    string value = args->value;
    // Проверка переданное число соотвествует начальной системе счисления
    for (auto i : value)
    {
        if (charactersInSourceSystem.find(i) == charactersInSourceSystem.end())
        {
            cout << "The number of the wrong number system\n";
            return 1;
        }
    }

    // Если нужная система совпадает с начальной
    if (sourceNotation == destinationNotation)
    {
        cout << value << endl;
        return 0;
    }

    // Перевод в десятичную
    int decimalNumber = 0;
    if (sourceNotation != 10)
    {
        ConvertToDecimalNotation(value, decimalNumber, sourceNotation);
    }
    else
    {
        StringToInt(value, decimalNumber, wasError);
    }

    // Если нужна десятичная
    if (destinationNotation == 10)
    {
        cout << decimalNumber << endl;
        return 0;
    }

    // Множество из символов нужной системы счисления
    set<char> charactersInDestinationSystem;
    for (int i = 0; i < destinationNotation; i++)
    {
        charactersInDestinationSystem.insert(CHARACTERS[i]);
    }

    // Перевод из десятичной системы в нужную
    int tempNumber = decimalNumber;
    string destinationNotationNumber = "";
    ConvertToDestinationNotation(tempNumber, destinationNotation, destinationNotationNumber);

    if (decimalNumber < 0)
    {
        destinationNotationNumber += "-";
    }
    else
    {
        destinationNotationNumber += CHARACTERS[tempNumber];
    }
    // Вывести число
    OutputNumber(destinationNotationNumber);

    return 0;
}