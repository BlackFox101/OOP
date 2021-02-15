#include <iostream>
#include <fstream>
#include <optional>
#include <string>

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

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    // Проверка правильности аргументов командной строки
    if (!args)
    {
        return 1;
    }

    return 0;
}
