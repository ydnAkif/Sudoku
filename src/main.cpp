#include <iostream>
#include "Sudoku.hpp"

using namespace std;

int main()
{
    Sudoku sudoku;
    cout << "\nBefore solving" << endl;
    sudoku.PrintBoard();

    auto startTime = std::chrono::high_resolution_clock::now();
    bool isSolved = sudoku.Solve();
    auto endTime = std::chrono::high_resolution_clock::now();

    if (isSolved)
    {
        cout << "\nAfter solving" << endl;
        sudoku.PrintBoard();
    }
    else //unsolvable board
        cout << "The board is unsolvable" << endl;

    sudoku.PrintSolveTime(startTime, endTime);

    system("Pause");
    return 0;
}