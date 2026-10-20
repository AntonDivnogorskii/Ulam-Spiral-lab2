#pragma once

#include <vector>

#include "LineInfo.h"

struct AlgorithmData {
    int startNumber = 0;
	int endNumber = 0;

    std::vector<std::vector<int>> spiralGrid;
    std::vector<std::vector<bool>> primeMask;

    double overallPrimeShare = 0.0;   // доля простых среди всех чисел спирали
    std::vector<LineInfo> richLines;  // линии с повышенной долей простых
};