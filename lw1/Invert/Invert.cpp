#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <cmath>

using namespace std;

struct Args
{
    string matrixFile;
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
    args.matrixFile = argv[1];

    return args;
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
    input.open(args->matrixFile);
    if (!input.is_open())
    {
        cout << "Failed to open '" << args->matrixFile << "' for reading\n";
        return 1;
    }

    const int MAX_LENGTH = 3;
    float matrix[MAX_LENGTH][MAX_LENGTH];

    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_LENGTH; j++)
        {
            if (input.eof())
            {
                return 1;
            }
            input >> matrix[i][j];
        }
    }

    float determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1]
                      - matrix[0][1] * matrix[1][0] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0]
                      + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0];

    float inverseMatrix[MAX_LENGTH][MAX_LENGTH];

    inverseMatrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) / determinant;
    inverseMatrix[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) / determinant;
    inverseMatrix[2][0] = (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]) / determinant;
    inverseMatrix[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) / determinant;
    inverseMatrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) / determinant;
    inverseMatrix[2][1] = (matrix[2][0] * matrix[0][1] - matrix[0][0] * matrix[2][1]) / determinant;
    inverseMatrix[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) / determinant;
    inverseMatrix[1][2] = (matrix[1][0] * matrix[0][2] - matrix[0][0] * matrix[1][2]) / determinant;
    inverseMatrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) / determinant;

    for (int i = 0; i < MAX_LENGTH; i++)
    {
        for (int j = 0; j < MAX_LENGTH; j++)
        {
            cout << round(inverseMatrix[i][j]*1000)/1000 << " ";
        }
        cout << "\n";
    }

    if (input.bad())
    {
        std::cout << "Failed to read data from input file\n";
        return 1;
    }

    return 0;
}
