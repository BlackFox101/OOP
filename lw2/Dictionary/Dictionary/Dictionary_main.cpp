#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <Windows.h>

#include "Dictionary.h"

using namespace std;

string ParseArgs(int argc, char* argv[])
{
    if (argc == 1)
    {
        return "";
    }

    return argv[1];
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string fileName = ParseArgs(argc, argv);

    map<string, string> dictionary;

    fstream vocabulary;
    if (OpenFile(vocabulary, fileName))
    {
        InitDictionary(vocabulary, dictionary);
    }

    WorkingDictionary(vocabulary, dictionary);

    return 0;
}