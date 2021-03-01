#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <cmath>
#include "Invert.h"

using namespace std;
const int MAX_LENGTH = 3;
typedef float Matrix3x3[MAX_LENGTH][MAX_LENGTH];

struct Args
{
    string matrixFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage Invert.exe <matrix file>\n";
        return std::nullopt;
    }
    Args args;
    args.matrixFileName = argv[1];

    return args;
}

void OutputMatrix(Matrix3x3 matrix)
{
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_LENGTH; j++)
        {
            cout << round(matrix[i][j] * 1000) / 1000;
            if (j != 2)
            {
                cout << "\t";
            }
        }
        cout << "\n";
    }
}

float FindDeterminant(const Matrix3x3 matrix)
{
    // Находим определительм матрицы
    float determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1]
                      - matrix[0][1] * matrix[1][0] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0]
                      + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0];

    return determinant;
}

void TransposeAndCalcMinor(Matrix3x3 inverseMatrix, const Matrix3x3 matrix, const float determinant)
{
    // Высчитываем миноры и высчитываем обратную матрицу
    inverseMatrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) / determinant;
    inverseMatrix[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) / determinant;
    inverseMatrix[2][0] = (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]) / determinant;
    inverseMatrix[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) / determinant;
    inverseMatrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) / determinant;
    inverseMatrix[2][1] = (matrix[2][0] * matrix[0][1] - matrix[0][0] * matrix[2][1]) / determinant;
    inverseMatrix[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) / determinant;
    inverseMatrix[1][2] = (matrix[1][0] * matrix[0][2] - matrix[0][0] * matrix[1][2]) / determinant;
    inverseMatrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) / determinant;
}

void FindInverseMatrix(Matrix3x3 inversiveMatrix, Matrix3x3 matrix, bool& wasError)
{
    // Найти определитель
    const float determinant = FindDeterminant(matrix);
    if (determinant == 0)
    {
        cout << "The inverse matrix cannot be found, since the determinant of the matrix is zero!\n" ;
        wasError = true;
        return;
    }

    // Транспонирование и вычисление миноров
    TransposeAndCalcMinor(inversiveMatrix, matrix, determinant);
}

void ReadMatrixFromFile(ifstream& input, Matrix3x3 matrix, bool& wasError)
{
    // Считываем матрицу из файла
    string str;
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_LENGTH; j++)
        {
            // Проверка на полную матрицу
            if (input.eof())
            {
                cout << "The matrix is not complete!\n";
                wasError = true;
                return;
            }

            input >> str;

            // Проверка на пустой файл
            if (str.length() == 0)
            {
                cout << "The matrixFile is empty!\n";
                wasError = true;
                return;
            }

            // Проверка элемента матрицы на число
            size_t pos;
            float number = stof(str, &pos);
            if (pos != str.length())
            {
                cout << "The matrix does not specify a number: " << str << endl;
                wasError = true;
                return;
            }

            matrix[i][j] = number;
        }
        getline(input, str); // После прочтения в строке 3-x элементов остальное пропустить
    }
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
    input.open(args->matrixFileName);
    if (!input.is_open())
    {
        cout << "Failed to open '" << args->matrixFileName << "' for reading\n";
        return 1;
    }

    Matrix3x3 matrix;

    bool wasError = false;
    ReadMatrixFromFile(input, matrix, wasError);
    if (wasError)
    {
        return 1;
    }

    Matrix3x3 inverseMatrix;
    FindInverseMatrix(inverseMatrix, matrix, wasError);
    if (wasError)
    {
        return 1;
    }

    if (input.bad())
    {
        cout << "Failed to read data from input file\n";
        return 1;
    }

    OutputMatrix(inverseMatrix);

    return 0;
}