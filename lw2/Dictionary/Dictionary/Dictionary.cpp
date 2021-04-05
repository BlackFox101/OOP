#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "Dictionary.h"

using namespace std;

bool OpenFile(fstream& file, string fileName)
{
    file.open(fileName);
    if (!file.is_open())
    {
        return false;
    }

    return true;
}

void InitDictionary(fstream& initFile, map<string, string>& dictionary)
{
    string line;
    while (getline(initFile, line))
    {
        if (line.find("-") == std::string::npos)
        {
            break;;
        }
        string eng = line.substr(0, line.find("-"));
        string rus = line.substr(eng.length() + 1);

        dictionary[eng] = rus;
    }
}

void SaveDictionary(fstream& vocabularyFile, const map<string, string>& dictionary)
{
    map<string, string>::const_iterator it;
    for (it = dictionary.begin(); it != dictionary.end(); ++it) {
        vocabularyFile << it->first << "-" << it->second << endl;
    }
}

void Save(fstream& vocabularyFile, const map<string, string>& dictionary)
{
    if (vocabularyFile.is_open())
    {
        vocabularyFile.clear();
        vocabularyFile.seekg(0);
        SaveDictionary(vocabularyFile, dictionary);

        return;
    }

    fstream output;
    while (true)
    {
        cout << "¬ведите место дл€ сохранени€ файла:";
        string path;
        cin >> path;
        output.open(path);

        if (!output.is_open())
        {
            cout << "Failed to open '"<< path <<"' for writing\n";
            continue;
        }
        break;
    }
    
    SaveDictionary(output, dictionary);
}

bool SaveWord(map<string, string>& dictionary, const string& word, bool& wasChange, istream& input)
{
    string translation;
    getline(input, translation);
    if (translation != "")
    {
        dictionary[word] = translation;
        wasChange = true;
        return true;
    }
    return false;
}

bool TranslateWord(const string& word, const map<string, string>& dictionary, ostream& output)
{
    if (dictionary.find(word) != dictionary.end())
    {
        output << dictionary.at(word) << endl;
        return true;
    }
    return false;
}

void WorkingDictionary(fstream& vocabularyFile, map<string, string>& dictionary)
{
    string word;
    bool wasChange = false;
    getline(cin, word);
    while (word != "...")
    {
        string tempWord = word;
        transform(word.begin(), word.end(), word.begin(), tolower);

        if (!TranslateWord(word, dictionary, cout))
        {
            cout << "Ќеизвестное слово У" << tempWord << "Ф. ¬ведите перевод или пустую строку дл€ отказа.\n";
            if (SaveWord(dictionary, word, wasChange, cin))
            {
                cout << "—лово У" << tempWord << "Ф сохранено в словаре как У" << dictionary[word] << "Ф.\n";
                wasChange = true;
            }
            else
            {
                cout << "—лово У" << tempWord << "Фпроигнорировано.\n";
            }
        }
        getline(cin, word);
    }

    if (wasChange)
    {
        char ch;
        cout << "¬ словарь были внесены изменени€. ¬ведите Y или y дл€ сохранени€ перед выходом.\n";
        cin >> ch;
        if (ch == 'Y' || ch == 'y')
        {
            Save(vocabularyFile, dictionary);
            cout << "»зменени€ сохранены. ƒо свидани€.\n";
        }
    }
}