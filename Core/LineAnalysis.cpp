#include "LineAnalysis.h"
#include <algorithm>

namespace {
    // Линии короче не рассматриваются: по ним статистика ненадёжна
    const int kMinLineLength = 5;

    // Линия считается «богатой», если доля простых на ней минимум
    // во столько раз больше средней доли по всей спирали
    const double kRichFactor = 2.0;

    // Сколько лучших линий оставить
    const size_t kMaxLines = 10;

    // Направления обхода: смещение по строке и по столбцу
    // 0 - по строке, 1 - по столбцу, 2 - диагональ вниз-вправо, 3 - диагональ вниз-влево
    const int kDirectionRow[] = { 0, 1, 1, 1 };
    const int kDirectionCol[] = { 1, 0, 1, -1 };

    // Вторая разность трёх чисел подряд. long long, потому что 2 * число
    // может не поместиться в int
    long long SecondDifference(int first, int second, int third) {
        return static_cast<long long>(third) - 2LL * second + first;
    }

    // Разбивает один непрерывный набор чисел линии на куски с постоянной формулой
    // и сохраняет каждый кусок в result
    void AnalyzeRun(const std::vector<int>& values, const std::vector<bool>& primes,
        int direction, std::vector<LineInfo>& result) {
        const int count = static_cast<int>(values.size());

        int i = 0;
        while (i + 2 < count) {
            // Тройка с второй разностью не 8 не лежит на формуле 4t^2 + ..., пропускаем
            if (SecondDifference(values[i], values[i + 1], values[i + 2]) != 8) {
                i++;
                continue;
            }

            // Тройка подходит, растягиваем кусок вправо, пока вторая разность равна 8
            int end = i + 2;
            while (end + 1 < count &&
                SecondDifference(values[end - 1], values[end], values[end + 1]) == 8) {
                end++;
            }

            // Формула куска: f(t) = 4t^2 + b*t + c, где t = 0 это values[i]
            LineInfo line;
            line.a = 4;
            line.c = values[i];
            line.b = values[i + 1] - values[i] - 4;
            line.length = end - i + 1;
            line.direction = direction;

            for (int k = i; k <= end; k++) {
                if (primes[k]) {
                    line.primeCount++;
                }
            }
            line.primeShare = static_cast<double>(line.primeCount) / line.length;

            result.push_back(line);

            // Следующий кусок начинаем с последней клетки этого:
            // на стыке формул эта клетка принадлежит обеим
            i = end;
        }
    }
}

void LineAnalysis::FindRichLines(AlgorithmData& algorithmData) {
    const int side = static_cast<int>(algorithmData.spiralGrid.size());

    // Доля простых среди всех заполненных клеток (с чем будем сравнивать линии)
    int filledCells = 0;
    int primeCells = 0;

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            if (algorithmData.spiralGrid[i][j] != 0) {
                filledCells++;

                if (algorithmData.primeMask[i][j]) {
                    primeCells++;
                }
            }
        }
    }

    algorithmData.overallPrimeShare =
        filledCells > 0 ? static_cast<double>(primeCells) / filledCells : 0.0;

    std::vector<LineInfo> allLines;

    for (int direction = 0; direction < 4; direction++) {
        const int dRow = kDirectionRow[direction];
        const int dCol = kDirectionCol[direction];

        for (int startRow = 0; startRow < side; startRow++) {
            for (int startCol = 0; startCol < side; startCol++) {

                // Линия начинается в клетке, перед которой (против направления)
                // уже нет клеток сетки
                const int prevRow = startRow - dRow;
                const int prevCol = startCol - dCol;
                const bool prevInside = prevRow >= 0 && prevRow < side && prevCol >= 0 && prevCol < side;

                if (prevInside) {
                    continue;
                }

                // Идём по линии и собираем числа и признак «простое»
                std::vector<int> values;
                std::vector<bool> primes;

                int row = startRow;
                int col = startCol;

                while (row < side && col >= 0 && col < side) {
                    const int number = algorithmData.spiralGrid[row][col];

                    if (number == 0) {
                        // Пустая клетка обрывает линию: анализируем то, что собрали
                        AnalyzeRun(values, primes, direction, allLines);
                        values.clear();
                        primes.clear();
                    }
                    else {
                        values.push_back(number);
                        primes.push_back(algorithmData.primeMask[row][col]);
                    }

                    row += dRow;
                    col += dCol;
                }

                AnalyzeRun(values, primes, direction, allLines);
            }
        }
    }

    // Оставляем только длинные линии с высокой долей простых
    algorithmData.richLines.clear();

    for (const LineInfo& line : allLines) {
        if (line.length >= kMinLineLength &&
            line.primeCount > 0 &&
            line.primeShare >= kRichFactor * algorithmData.overallPrimeShare) {
            algorithmData.richLines.push_back(line);
        }
    }

    // Сначала с наибольшей долей, при равенстве длинные
    std::sort(algorithmData.richLines.begin(), algorithmData.richLines.end(),
        [](const LineInfo& left, const LineInfo& right) {
            if (left.primeShare != right.primeShare) {
                return left.primeShare > right.primeShare;
            }
            return left.length > right.length;
        });

    if (algorithmData.richLines.size() > kMaxLines) {
        algorithmData.richLines.resize(kMaxLines);
    }
}