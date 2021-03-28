#pragma once
#include <iosfwd>
#include <optional>
#include <string>
#include <vector>

using namespace std;

bool OpenFile(fstream& file, string fileName);

void InitDictionary(fstream& initFile, map<string, string>& dictionary);

void WorkingDictionary(fstream& vocabularyFile, map<string, string>& dictionary);