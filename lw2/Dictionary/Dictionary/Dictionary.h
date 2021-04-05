#pragma once
#include <iosfwd>
#include <optional>
#include <string>
#include <vector>

using namespace std;

bool OpenFile(fstream& file, string fileName);

void InitDictionary(fstream& initFile, map<string, string>& dictionary);

bool SaveWord(map<string, string>& dictionary, const string& word, bool& wasChange, istream& input);

bool TranslateWord(const string& word, const map<string, string>& dictionary, ostream& output);

void WorkingDictionary(fstream& vocabularyFile, map<string, string>& dictionary);