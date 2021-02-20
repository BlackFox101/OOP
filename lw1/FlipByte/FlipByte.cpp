#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <cmath>

using namespace std;

struct Args
{
    string byte;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage FlipByte.exe <input byte>\n";
        return std::nullopt;
    }
    Args args;
    args.byte = argv[1];

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

    int byte = 6;
    cout << (byte << );

    return 0;
}
