#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
    string inputFileName;
    string outputFileName;
    string search;
    string replace;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage Replace.exe <input file> <output file> <search string> <replace string>\n";
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.search = argv[3];
    args.replace = argv[4];

    return args;
}

string replaceString(string& line, string& search, string& replace)
{
    string str = "";
    size_t pos = 0; // Целочисленный тип без знака, первое вхождение подстроки
    while (pos < line.length())
    {
        size_t foundPos = line.find(search, pos);
        if (foundPos == -1 || search == "")
        {
            str = str + line.substr(pos, line.length() - pos);
            pos = line.length();
        }
        else
        {
            str = str + line.substr(pos, foundPos - pos);
            str = str + replace;
            pos = pos + foundPos + search.length();
        }
    }
    return str;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    // Проверка правильности аргументов командной строки
    if (!args)
    {
        return 1;
    }

    // Открываем входной файл
    ifstream input;
    input.open(args->inputFileName);
    if (!input.is_open())
    {
        std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
        return 1;
    }
    // Открваем входной файл
    ofstream output;
    output.open(args->outputFileName);
    if (!output.is_open())
    {
        std::cout << "Failed to open '" << args->outputFileName << "' for writing\n";
        return 1;
    }

    string line;
    while (getline(input, line))
    {
        output << replaceString(line, args->search, args->replace) << endl;
    }

    if (input.bad())
    {
        std::cout << "Failed to read data from input file\n";
        return 1;
    }

    if (!output.flush())
    {
        std::cout << "Failed to write data to output file\n";
        return 1;
    }

    return 0;
}