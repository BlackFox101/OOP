#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <cmath>
#include "Invert.h"

using namespace std;

const int MAX_LENGTH = 3;

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

void OutputMatrix(float matrix[3][3])
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

float FindDeterminant(float  matrix[3][3])
{
    // Находим определительм матрицы
    float determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1]
                      - matrix[0][1] * matrix[1][0] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0]
                      + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0];

    return determinant;
}

void TransposeAndCalcMinor(float inverseMatrix[3][3], float matrix[3][3], const float determinant)
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

void FindInverseMatrix(float  matrix[3][3], const float& determinant)
{

    // Транспонирование и вычисление миноров
    float inverseMatrix[MAX_LENGTH][MAX_LENGTH];
    TransposeAndCalcMinor(inverseMatrix, matrix, determinant);

    // Вывод обратной матрицы
    OutputMatrix(inverseMatrix);
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

    float matrix[MAX_LENGTH][MAX_LENGTH];

    // Считываем матрицу из файла
    string str = "";
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_LENGTH; j++)
        {
            // Проверка на полную матрицу
            if (input.eof())
            {
                cout << "The matrix is not complete!\n";
                return 1;
            }

            input >> str;

            // Проверка на пустой файл
            if (str.length() == 0)
            {
                cout << "The matrixFile is empty!\n";
                return 1;
            }
            
            // Проверка элемента матрицы на число
            size_t pos;
            float number = stof(str, &pos);
            if (pos != str.length())
            {
                cout << "The matrix does not specify a number: " << str << endl;
                return 1;
            }

            matrix[i][j] = number;
        }
        getline(input, str); // После прочтения в строке 3-x элементов остальное пропустить
    }

    // Найти определитель
    const float determinant = FindDeterminant(matrix);
    if (determinant == 0)
    {
        cout << "The inverse matrix cannot be found, since the determinant of the matrix is zero!\n" ;
        return 1;
    }

    FindInverseMatrix(matrix, determinant);

    if (input.bad())
    {
        cout << "Failed to read data from input file\n";
        return 1;
    }

    return 0;
}