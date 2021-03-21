#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <queue>
#include <vector>

using namespace std;

struct Point
{
    int x;
    int y;
};

struct Args
{
    string inputFileName;
    string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage fill.exe <input file> <output file>\n";
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];

    return args;
}

void PaintAndPushToQueue(Point pt, vector<vector<char>>& matrix, const int lines, const int columns, queue<Point>& cells)
{
    if (matrix[pt.x][pt.y] == ' ')
    {
        matrix[pt.x][pt.y] = '.';
        cells.push(pt);
    }
}

void Fill(Point firstPoint, vector<vector<char>>& matrix, const int lines, const int columns, queue<Point>& cells)
{
    cells.push(firstPoint);

    while (!cells.empty())
    {
        Point pt = cells.front();
        cells.pop();

        if (pt.x + 1 < lines && pt.y < columns)
        {
            PaintAndPushToQueue({ pt.x + 1, pt.y }, matrix, lines, columns, cells);
        }

        if (pt.x - 1 < lines && pt.x - 1 >= 0 && pt.y < columns)
        {
            PaintAndPushToQueue({ pt.x - 1, pt.y }, matrix, lines, columns, cells);
        }

        if (pt.x < lines && pt.y + 1 < columns)
        {
            PaintAndPushToQueue({ pt.x, pt.y + 1 }, matrix, lines, columns, cells);
        }

        if (pt.x < lines && pt.y - 1 < columns && pt.y - 1 >= 0)
        {
            PaintAndPushToQueue({ pt.x, pt.y - 1 }, matrix, lines, columns, cells);
        }
    }
}

void CountLinesAndColumnsFromFile(ifstream& input, int& columnsCounter, int& linesCounter)
{
    string line;
    while (getline(input, line))
    {
        if (columnsCounter < line.length())
        {
            columnsCounter = line.length();
        }
        linesCounter++;
    }
}

void FillingMatrix(vector<vector<char>>& matrix, const int linesCounter, const int columnsCounter, const char symbol)
{
    for (int i = 0; i < linesCounter; i++)
    {
        for (int j = 0; j < columnsCounter; j++)
        {
            matrix[i][j] = symbol;
        }
    }
}

void ReadСontoursFromFile(int linesCounter, ifstream& input, vector<vector<char>>& matrix)
{
    string line;
    for (int i = 0; i < linesCounter; i++)
    {
        getline(input, line);
        for (int j = 0; j < line.length(); j++)
        {
            matrix[i][j] = line[j];
        }
    }
}

void FillingAreas(const int linesCounter, const int columnsCounter, vector<vector<char>>& matrix)
{
    queue<Point> cells;
    for (int i = 0; i < linesCounter; i++)
    {
        for (int j = 0; j < columnsCounter; j++)
        {
            if (matrix[i][j] == 'O')
            {
                Fill({ i, j }, matrix, linesCounter, columnsCounter, cells);
            }
        }
    }
}

void OutputMatrix(ofstream& output, vector<vector<char>> matrix, const int linesCounter, const int columnsCounter)
{
    for (int i = 0; i < linesCounter; i++)
    {
        for (int j = 0; j < columnsCounter; j++)
        {
            output << matrix[i][j];
        }
        output << endl;
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
    input.open(args->inputFileName);
    if (!input.is_open())
    {
        cout << "Failed to open '" << args->inputFileName << "' for reading\n";
        return 1;
    }
    // Открваем входной файл
    ofstream output;
    output.open(args->outputFileName);
    if (!output.is_open())
    {
        cout << "Failed to open '" << args->outputFileName << "' for writing\n";
        return 1;
    }

    int linesCounter = 0;
    int columnsCounter = 0;
    // Подсчет количества строк и максимальную длину строки в файле
    CountLinesAndColumnsFromFile(input, columnsCounter, linesCounter);

    if (linesCounter == 0 && columnsCounter == 0)
    {
        cout << "File is empty\n";
        return 1;
    }

    vector<vector<char> > matrix(linesCounter, vector<char>(columnsCounter));

    // Заполнить нужную область массива пробел
    FillingMatrix(matrix, linesCounter, columnsCounter, ' ');

    input.clear();
    input.seekg(0);
    // Считать контуры с файла
    ReadСontoursFromFile(linesCounter, input, matrix);

    FillingAreas(linesCounter, columnsCounter, matrix);

    // Вывести матрицу
    OutputMatrix(output, matrix, linesCounter, columnsCounter);

    if (input.bad())
    {
        cout << "Failed to read data from input file\n";
        return 1;
    }

    if (!output.flush())
    {
        std::cout << "Failed to write data to output file\n";
        return 1;
    }

    return 0;
}