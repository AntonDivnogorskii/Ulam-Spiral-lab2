#include "PrimeSieve.h"

#include <cmath>
#include <algorithm>

// Обычное решето Эратосфена: возвращает все простые числа от 2 до limit
std::vector<int> PrimeSieve::FindSmallPrimes(int limit) {
    
    // isComposite[k] == true означает «число k составное».
    // Сначала все false (пока считаем все числа простыми).
    // Размер limit + 1, чтобы индекс limit существовал.
    std::vector<bool> isComposite(limit + 1, false);

    // Сюда складываем найденные простые числа
    std::vector<int> primes;

    for (int i = 2; i <= limit; i++) {
        // Если i ещё не вычеркнуто, на него не делится ни одно меньшее простое,
        // значит, i простое
        if (!isComposite[i]) {
            primes.push_back(i);

            // Вычёркиваем кратные i, начиная с i*i: меньшие кратные (2i, 3i...)
            // уже вычеркнуты меньшими простыми.
            // long long нужен, чтобы i*i не переполнило int
            for (long long j = static_cast<long long>(i) * i; j <= limit; j += i) {
                isComposite[j] = true;
            }
        }
    }

    return primes;
}


// Сегментное решето: проверяет на простоту отрезок [first; last].
// Результат: isPrime[n - first] == true, если число n простое
std::vector<bool> PrimeSieve::SieveSegment(long long first, long long last) {

    // Массив ровно на длину отрезка. Число n лежит в ячейке n - first
    // (например, для отрезка 100...120 число 113 лежит в ячейке 13).
    // Сначала все числа считаем простыми
    std::vector<bool> isPrime(last - first + 1, true);

    // Числа меньше 2 (0 и 1) не простые.
    // Цикл сработает, только если отрезок захватывает такие числа
    for (long long n = first; n < 2 && n <= last; n++) {
        isPrime[n - first] = false;
    }

    // Простые делители нужны только до корня из last: у любого составного числа
    // есть простой делитель не больше его корня. +1 берём с запасом
    // на неточность вычисления корня
    int limit = static_cast<int>(std::sqrt(static_cast<double>(last))) + 1;
    std::vector<int> smallPrimes = FindSmallPrimes(limit);

    for (int prime : smallPrimes) {
        long long p = prime;

        // Если p*p уже больше конца отрезка, у оставшихся простых
        // в отрезке нет чисел для вычёркивания
        if (p * p > last) break;

        // Первое кратное p, которое не меньше first
        // (целочисленное деление с округлением вверх).
        // Например, p = 7, first = 100: (106 / 7) * 7 = 105
        long long begin = ((first + p - 1) / p) * p;

        // Начинаем не раньше p*p, чтобы не вычеркнуть само простое число p,
        // если оно попадает в отрезок
        if (begin < p * p) begin = p * p;

        // Вычёркиваем кратные p шагом p до конца отрезка
        for (long long m = begin; m <= last; m += p) {
            isPrime[m - first] = false;
        }
    }

    // Невычеркнутые числа (true) простые
    return isPrime;
}

void PrimeSieve::MarkPrimesInSpiral(AlgorithmData& algorithmData) {
    // Сторона спирали
    const int side = static_cast<int>(algorithmData.spiralGrid.size());

    // Границы отрезка, по которому строили спираль
    const long long first = algorithmData.startNumber;
    const long long last = algorithmData.endNumber;

    // Решето по линейному отрезку
    std::vector<bool> isPrime = SieveSegment(first, last);

    // Маска того же размера, что и спираль
    algorithmData.primeMask.assign(side, std::vector<bool>(side, false));

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            const long long number = algorithmData.spiralGrid[i][j];

            // Пустые клетки (0) и любые числа вне отрезка пропускаются
            if (number >= first && number <= last) {
                algorithmData.primeMask[i][j] = isPrime[number - first];
            }
        }
    }
}