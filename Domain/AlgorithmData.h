#pragma once

#include <vector>

struct AlgorithmData {
    int startNumber = 0;
	int lengthOfSideOfSquare = 0;

    std::vector<std::vector<int>> spiralGrid;
    std::vector<std::vector<bool>> primeMask;
};