#include "Sudoku.hpp"

Sudoku::Sudoku() {
    board = {{0, 9, 0, 6, 3, 0, 0, 1, 0},
             {0, 0, 0, 0, 7, 5, 6, 0, 0},
             {0, 0, 0, 9, 0, 0, 5, 7, 0},
             {0, 8, 1, 0, 0, 6, 0, 0, 0},
             {0, 0, 0, 1, 0, 0, 0, 0, 2},
             {0, 0, 0, 8, 0, 0, 1, 0, 0},
             {2, 0, 6, 0, 0, 0, 4, 0, 0},
             {4, 0, 0, 0, 6, 0, 7, 8, 0},
             {5, 0, 0, 0, 0, 9, 0, 0, 0}};
    rowLen = board.size();
    colLen = board[0].size();
    gridHeight = 3;
    gridWidth = 3;
    numberChoices = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

Sudoku::~Sudoku() = default;

void Sudoku::PrintSolveTime(std::chrono::high_resolution_clock::time_point startTime,
                            std::chrono::high_resolution_clock::time_point endTime) {
    auto timeTakenInSeconds = std::chrono::duration_cast<std::chrono::seconds>(
            endTime - startTime)
            .count();
    auto timeTakenInMilliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(
            endTime - startTime)
            .count();
    std::cout << "\nTime taken to solve : " << timeTakenInSeconds << "."
              << timeTakenInMilliSeconds % long(1E+3) << " seconds" << std::endl;
}

void Sudoku::PrintBoard() {
    for (int row = 0; row < rowLen; ++row) {
        if (row == 0 || row % gridHeight == 0)
            std::cout << "+-------+-------+-------+" << std::endl;
        for (int col = 0; col < colLen; ++col) {
            if (col == 0 || col % gridWidth == 0)
                std::cout << "| ";
            if (col == colLen - 1)
                std::cout << board[row][col] << " |" << std::endl;
            else
                std::cout << board[row][col] << " ";
        }
    }
    std::cout << "+-------+-------+-------+" << std::endl;
}

SquarePosition Sudoku::GetEmptyPosition() {
    SquarePosition square;
    for (int row = 0; row < rowLen; ++row) {
        for (int col = 0; col < colLen; ++col) {
            if (board[row][col] == 0) {
                square.rowPosition = row;
                square.colPosition = col;
                return square;
            }
        }
    }
    return square;
}

bool Sudoku::IsValid(int number, int currentRow, int currentCol) {
    // check if number already exists in any other column in the same row
    for (int col = 0; col < colLen; ++col) {
        if (board[currentRow][col] == number && col != currentCol)
            return false;
    }
    // check if number already exists in any other row in the same column
    for (int row = 0; row < rowLen; ++row) {
        if (board[row][currentCol] == number && row != currentRow)
            return false;
    }
    // check if number already exists in any other position in the 3x3 grid
    int gridRowStartIndex = (currentRow / gridHeight) * 3,
            gridColStartIndex = (currentCol / gridWidth) * 3;
    int gridRowEndIndex = gridRowStartIndex + gridHeight,
            gridColEndIndex = gridColStartIndex + gridWidth;
    for (int row = gridRowStartIndex; row < gridRowEndIndex; ++row) {
        for (int col = gridColStartIndex; col < gridColEndIndex; ++col) {
            if (board[row][col] == number && row != currentRow && col != currentCol)
                return false;
        }
    }
    return true;
}

bool Sudoku::Solve() {
    SquarePosition emptyPosition = GetEmptyPosition();
    // if no square is empty it means board is solved

    if (emptyPosition.rowPosition == -1 ||
        emptyPosition.colPosition == -1)
        return true;
    int currentRow = emptyPosition.rowPosition,
            currentCol = emptyPosition.colPosition;
    for (auto number : numberChoices) {
        if (IsValid(number, currentRow, currentCol)) {
            board[currentRow][currentCol] = number;
            if (Solve())
                return true;
            // the board was unable to be solved at some point
            // so reset all values till last solved position
            board[currentRow][currentCol] = 0;
        }
    }
    return false;
}