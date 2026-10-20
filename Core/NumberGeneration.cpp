#include "NumberGeneration.h"

void NumberGeneration::GenerateDataForSpiral(AlgorithmData& algorithmData) {
    const int side = algorithmData.lengthOfSideOfSquare;

    // side строк по side нулей
    algorithmData.spiralGrid.assign(side, std::vector<int>(side, 0));

	// Начальная позиция в центре сетки
    int row = side / 2;
    int col = side / 2;

    // 
    int totalCells = side * side;
    int filledCells = 0;

    int currentNumber = algorithmData.startNumber;
    algorithmData.spiralGrid[row][col] = currentNumber++;
    filledCells++;

    const int dRow[] = { 0, -1, 0, 1 }; // вправо, вверх, влево, вниз
    const int dCol[] = { 1, 0, -1, 0 };

    int direction = 0;
    int stepLength = 1;
    int turnsCount = 0;

    while (filledCells < totalCells) {
        for (int i = 0; i < stepLength && filledCells < totalCells; i++) {
            row += dRow[direction];
            col += dCol[direction];

            if (row >= 0 && row < side && col >= 0 && col < side) {
                algorithmData.spiralGrid[row][col] = currentNumber;
                filledCells++;
            }

            currentNumber++;
        }

        direction = (direction + 1) % 4;
        turnsCount++;

        if (turnsCount % 2 == 0) {
            stepLength++;
        }
    }
}
