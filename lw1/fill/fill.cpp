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

typedef vector<vector<char>> Picture;

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

void PaintAndPushToQueue(Point pt, Picture& matrix, queue<Point>& cells)
{
    if (matrix[pt.x][pt.y] == ' ')
    {
        matrix[pt.x][pt.y] = '.';
        cells.push(pt);
    }
}

void Fill(Point firstPoint, Picture& matrix)
{
    int lines = matrix.size();
    int columns = matrix[0].size();
    queue<Point> cells;
    cells.push(firstPoint);

    while (!cells.empty())
    {
        Point pt = cells.front();
        cells.pop();

        if (pt.x + 1 < lines && pt.y < columns)
        {
            PaintAndPushToQueue({ pt.x + 1, pt.y }, matrix, cells);
        }

        if (pt.x - 1 < lines && pt.x - 1 >= 0 && pt.y < columns)
        {
            PaintAndPushToQueue({ pt.x - 1, pt.y }, matrix, cells);
        }

        if (pt.x < lines && pt.y + 1 < columns)
        {
            PaintAndPushToQueue({ pt.x, pt.y + 1 }, matrix, cells);
        }

        if (pt.x < lines && pt.y - 1 < columns && pt.y - 1 >= 0)
        {
            PaintAndPushToQueue({ pt.x, pt.y - 1 }, matrix, cells);
        }
    }
}

void CountLinesAndColumnsFromFile(istream& input, int& linesCounter, int& columnsCounter)
{
    string line;
    while (getline(input, line))
    {
        if (columnsCounter < (int)line.length())
        {
            columnsCounter = line.length();
        }
        linesCounter++;
    }
}

Picture ReadContursFromFile(istream& input)
{
    int linesCounter = 0;
    int columnsCounter = 0;
    CountLinesAndColumnsFromFile(input, linesCounter, columnsCounter);
    if (linesCounter == 0 && columnsCounter == 0)
    {
        return {};
    }

    Picture matrix(linesCounter, vector<char>(columnsCounter));

    input.clear();
    input.seekg(0);
    string line;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        getline(input, line);
        for (size_t j = 0; j < line.length(); j++)
        {
            matrix[i][j] = line[j];
        }
        for (size_t j = line.length(); j < matrix[0].size(); j++)
        {
            matrix[i][j] = ' ';
        }
    }

    return matrix;
}

void FillingAreas(Picture& matrix)
{
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[0].size(); j++)
        {
            if (matrix[i][j] == 'O')
            {
                Fill({ i, j }, matrix);
            }
        }
    }
}

void OutputMatrix(ostream& output, const Picture& matrix)
{
    for (int i = 0; i < (int)matrix.size(); i++)
    {
        for (int j = 0; j < (int)matrix[0].size(); j++)
        {
            output << matrix[i][j];
        }
        output << endl;
    }
}

bool OpenInputOutputFiles(ifstream& input, ofstream& output, string inputFileName, string outputFileName)
{
    input.open(inputFileName);
    if (!input.is_open())
    {
        cout << "Failed to open '" << inputFileName << "' for reading\n";
        return false;
    }

    output.open(outputFileName);
    if (!output.is_open())
    {
        cout << "Failed to open '" << outputFileName << "' for writing\n";
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    // Проверка правильности аргументов командной строки
    if (!args)
    {
        return 1;
    }

    ifstream input;
    ofstream output;
    if (!OpenInputOutputFiles(input, output, args->inputFileName, args->outputFileName))
    {
        return 1;
    }

    Picture matrix = ReadContursFromFile(input);
    if (matrix.empty())
    {
        cout << "File is empty!\n";
        return 1;
    }

    FillingAreas(matrix);

    OutputMatrix(output, matrix);

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