#pragma once

#include <vector>
#include "../Domain/AlgorithmData.h"

class PrimeSieve {
public:
    // Заполняет algorithmData.primeMask по уже построенной спирали
    void MarkPrimesInSpiral(AlgorithmData& algorithmData);

private:
    // Обычное решето Эратосфена: простые от 2 до limit
    std::vector<int> FindSmallPrimes(int limit);

    // Сегментное решето: результат[n - first] == true, если n простое
    std::vector<bool> SieveSegment(long long first, long long last);
};