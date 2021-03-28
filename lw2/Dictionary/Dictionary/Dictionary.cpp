#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

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
        string eng = line.substr(0, line.find("-"));
        string rus = line.substr(eng.length() + 1);

        dictionary[eng] = rus;
    }
}

void SaveDictionary(fstream& vocabularyFile, map<string, string> dictionary)
{
    map<string, string>::iterator it;
    for (it = dictionary.begin(); it != dictionary.end(); ++it) {
        vocabularyFile << it->first << "-" << it->second << endl;
    }
}

void Save(fstream& vocabularyFile, map<string, string> dictionary)
{
    if (vocabularyFile.is_open())
    {
        vocabularyFile.clear();
        vocabularyFile.seekg(0);
        SaveDictionary(vocabularyFile, dictionary);

        return;
    }

    fstream output;
    output.open("Dictionary.txt");
    if (!output.is_open())
    {
        cout << "Failed to open 'Dictionary.txt' for writing\n";
        return;
    }
    SaveDictionary(output, dictionary);
}

void WorkingDictionary(fstream& vocabularyFile, map<string, string>& dictionary)
{
    string word;
    bool wasChange = false;
    getline(cin, word);
    while (word != "...")
    {
        string findWord = word;

        transform(word.begin(), word.end(), word.begin(), tolower);
        if (dictionary.find(word) != dictionary.end())
        {
            cout << dictionary[word] << endl;
        }
        else 
        {
            cout << "Ќеизвестное слово У"<< findWord <<"Ф. ¬ведите перевод или пустую строку дл€ отказа.\n";
            string translation;
            getline(cin, translation);
            if (translation != "")
            {
                dictionary[word] = translation;
                cout << "—лово У" << findWord << "Ф сохранено в словаре как У" << translation << "Ф.\n";
                wasChange = true;
            }
            else
            {
                cout << "—лово У" << findWord << "Фпроигнорировано.\n";
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