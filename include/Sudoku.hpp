#include <iostream>
#include <vector>
#include <chrono>
#include <array>

struct SquarePosition
{
    int rowPosition = -1, colPosition = -1;
};

class Sudoku
{
private:
    std::vector<std::vector<int>> board{};
    int rowLen;
    int colLen;
    int gridHeight;
    int gridWidth;
    std::array<int, 9> numberChoices{};

public:
    Sudoku();
    ~Sudoku();
    void PrintSolveTime(std::chrono::high_resolution_clock::time_point startTime,
                        std::chrono::high_resolution_clock::time_point endTime);
    void PrintBoard();
    SquarePosition GetUnfilledPosition();
    bool CanNumberBeInserted(int number, int currentRow, int currentCol);
    bool Solve();
};
