#pragma once

void CountLinesAndColumnsFromFile(std::ifstream& input, std::string& line, int& columnsCounter, int& linesCounter);

void FillingMatrix(int linesCounter, int columnsCounter, char  matrix[100][100]);

void ReadÑontoursFromFile(int linesCounter, std::ifstream& input, char  matrix[100][100]);

void FillingAreas(int linesCounter, int columnsCounter, char  matrix[100][100]);

void OutputMatrix(int linesCounter, int columnsCounter, std::ofstream& output, char  matrix[100][100]);
