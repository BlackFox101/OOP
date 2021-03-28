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
    vocabularyFile.clear();
    vocabularyFile.seekg(0);
    map<string, string>::iterator it;
    for (it = dictionary.begin(); it != dictionary.end(); ++it) {
        vocabularyFile << it->first << "-" << it->second << endl;
    }
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
            cout << "Неизвестное слово “"<< findWord <<"”. Введите перевод или пустую строку для отказа.\n";
            string translation;
            getline(cin, translation);
            if (translation != "")
            {
                dictionary[word] = translation;
                cout << "Слово “" << findWord << "” сохранено в словаре как “" << translation << "”.\n";
                wasChange = true;
            }
            else
            {
                cout << "Слово “" << findWord << "”проигнорировано.\n";
            }
        }
        getline(cin, word);
    }

    if (wasChange)
    {
        char ch;
        cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
        cin >> ch;
        if (ch == 'Y' || ch == 'y')
        {
            SaveDictionary(vocabularyFile, dictionary);
            cout << "Изменения сохранены. До свидания.\n";
        }
    }
}