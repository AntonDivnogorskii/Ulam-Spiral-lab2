#include "NumberGeneration.h"

void NumberGeneration::GenerateDataForSpiral(AlgorithmData& algorithmData) {
    // Сколько чисел нужно уложить в спираль
    const int totalNumbers = algorithmData.endNumber - algorithmData.startNumber + 1;

	// Определяем размер стороны сетки (должен быть нечетным)
    int sideOfGrid = 1;
    while (sideOfGrid * sideOfGrid < totalNumbers) {
        sideOfGrid += 2;
    }

    // sideOfGrid строк по sideOfGrid нулей
    algorithmData.spiralGrid.assign(sideOfGrid, std::vector<int>(sideOfGrid, 0));

	// Начальная позиция в центре сетки
    int row = sideOfGrid / 2;
    int col = sideOfGrid / 2;

	// Количество клеток, которые нужно заполнить и уже заполненных клеток
    int totalCells = sideOfGrid * sideOfGrid;
    int filledCells = 0;

    int currentNumber = algorithmData.startNumber;

    // Записываем центральную клетку
    algorithmData.spiralGrid[row][col] = currentNumber++;

    // Таблица направлений для смещения курсора 
    // ( вправо, вверх, влево, вниз )
    const int dRow[] = { 0, -1, 0, 1 };
    const int dCol[] = { 1, 0, -1, 0 };

	// Текущее направление
    int direction = 0;
	// Количество шагов в текущем направлении
    int stepLength = 1;
	// Счётчик поворотов (необходим для удлинения шага после двух поворотов)
    int turnsCount = 0;

    while (currentNumber <= algorithmData.endNumber) {
        for (int i = 0; i < stepLength && currentNumber <= algorithmData.endNumber; i++) {

            // Смещение курсора в текущем направлении
            row += dRow[direction];
            col += dCol[direction];

            algorithmData.spiralGrid[row][col] = currentNumber++;
        }

        // Поворот на 90 градусов
        direction = (direction + 1) % 4;

        // Считаем поворот и каждый второй раз удлиняем отрезок
        turnsCount++;

        if (turnsCount % 2 == 0) {
            stepLength++;
        }
    }
}
