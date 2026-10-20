#include "NumberGeneration.h"

void NumberGeneration::GenerateDataForSpiral(AlgorithmData& algorithmData) {
    const int sideOfGrid = algorithmData.lengthOfSideOfSquare;

    // sideOfGrid строк по sideOfGrid нулей
    algorithmData.spiralGrid.assign(sideOfGrid, std::vector<int>(sideOfGrid, 0));

	// Начальная позиция в центре сетки
    int row = sideOfGrid / 2;
    int col = sideOfGrid / 2;

	// Количество клеток, которые нужно заполнить
    int totalCells = sideOfGrid * sideOfGrid;

	// Количество уже заполненных клеток
    int filledCells = 0;

    int startNumber = algorithmData.startNumber;


    algorithmData.spiralGrid[row][col] = startNumber++;
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

            if (row >= 0 && row < sideOfGrid && col >= 0 && col < sideOfGrid) {
                algorithmData.spiralGrid[row][col] = startNumber;
                filledCells++;
            }

            startNumber++;
        }

        direction = (direction + 1) % 4;
        turnsCount++;

        if (turnsCount % 2 == 0) {
            stepLength++;
        }
    }
}
