#include "PrimeSieve.h"

#include <cmath>
#include <algorithm>

std::vector<int> PrimeSieve::FindSmallPrimes(int limit) {
    std::vector<bool> isComposite(limit + 1, false);
    std::vector<int> primes;

    for (int i = 2; i <= limit; i++) {
        if (!isComposite[i]) {
            primes.push_back(i);

            // кратные i меньше i*i уже вычеркнуты меньшими простыми
            for (long long j = static_cast<long long>(i) * i; j <= limit; j += i) {
                isComposite[j] = true;
            }
        }
    }

    return primes;
}

std::vector<bool> PrimeSieve::SieveSegment(long long first, long long last) {
    std::vector<bool> isPrime(last - first + 1, true);

    // числа меньше 2 не простые
    for (long long n = first; n < 2 && n <= last; n++) {
        isPrime[n - first] = false;
    }

    int limit = static_cast<int>(std::sqrt(static_cast<double>(last))) + 1;
    std::vector<int> smallPrimes = FindSmallPrimes(limit);

    for (int prime : smallPrimes) {
        long long p = prime;

        if (p * p > last) break;

        // первое кратное p, не меньшее first
        long long begin = ((first + p - 1) / p) * p;

        // не раньше p*p, чтобы не вычеркнуть само p
        if (begin < p * p) begin = p * p;

        for (long long m = begin; m <= last; m += p) {
            isPrime[m - first] = false;
        }
    }

    return isPrime;
}

void PrimeSieve::MarkPrimesInSpiral(AlgorithmData& algorithmData) {
    const int side = algorithmData.lengthOfSideOfSquare;

    long long first = algorithmData.startNumber;
    long long last = first;

    // Последнее число ищем по самой спирали: при чётной стороне
    // часть чисел уходит за границы, и максимум больше first + side*side - 1
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            last = std::max(last, static_cast<long long>(algorithmData.spiralGrid[i][j]));
        }
    }

    std::vector<bool> isPrime = SieveSegment(first, last);

    algorithmData.primeMask.assign(side, std::vector<bool>(side, false));

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            long long number = algorithmData.spiralGrid[i][j];

            // 0 в клетке значит «не заполнена» (бывает при чётной стороне)
            if (number >= first && number <= last) {
                algorithmData.primeMask[i][j] = isPrime[number - first];
            }
        }
    }
}