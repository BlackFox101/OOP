#pragma once

void FindInverseMatrix(float  matrix[3][3], const int& MAX_LENGTH);

void FindDeterminant(float& determinant, float  matrix[3][3]);

void Transpose(float  inverseMatrix[3][3], float  matrix[3][3], float determinant);

int ReadMatrix(std::ifstream& input, std::string& str, float  matrix[3][3], bool& retflag);

void OutputMatrix(float  inverseMatrix[3][3]);

int ReadMatrix(std::ifstream& input, float  matrix[3][3], bool& retflag);
