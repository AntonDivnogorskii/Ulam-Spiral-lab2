#include "Tests.h"

namespace {
	bool checkPrimeMask(const AlgorithmData& data, const std::vector<bool>& expected)
	{
		const size_t side = data.primeMask.size();
		if (side == 0 || expected.size() != side * side) {
			return false;
		}

		for (size_t row = 0; row < side; ++row) {
			if (data.primeMask[row].size() != side) {
				return false;
			}

			for (size_t column = 0; column < side; ++column) {
				if (data.primeMask[row][column] != expected[row * side + column]) {
					return false;
				}
			}
		}
		return true;
	}

	bool check(bool condition, int testNumber, const std::string& description)
	{
		if (condition) {
			return true;
		}

		std::cout << "Тест " << testNumber << " не пройден: " << description << "\n";
		return false;
	}
}

void Tests::runTests() 
{
	PrimeSieve primeSieve;
	NumberGeneration numberGeneration;
	LineAnalysis lineAnalysis;

	// Тест 1: простые числа на диапазоне 1..10.
	{
		AlgorithmData data;
		data.startNumber = 1;
		data.endNumber = 10;
		data.spiralGrid = {
			{ 1, 2, 3, 4 },
			{ 5, 6, 7, 8 },
			{ 9, 10, 0, 0 },
			{ 0, 0, 0, 0 }
		};
		primeSieve.MarkPrimesInSpiral(data);

		if (!check(checkPrimeMask(data,
			{ false, true, true, false,
				true, false, true, false,
				false, false, false, false,
				false, false, false, false }),
			1, "неверно определены простые числа от 1 до 10")) {
			return;
		}
	}

	// Тест 2: сегментное решето на диапазоне, начинающемся со 100.
	{
		AlgorithmData data;
		data.startNumber = 100;
		data.endNumber = 120;
		data.spiralGrid = {
			{ 100, 101, 102, 103, 104 },
			{ 105, 106, 107, 108, 109 },
			{ 110, 111, 112, 113, 114 },
			{ 115, 116, 117, 118, 119 },
			{ 120, 0, 0, 0, 0 }
		};
		primeSieve.MarkPrimesInSpiral(data);

		if (!check(checkPrimeMask(data,
			{ false, true, false, true, false,
				false, false, true, false, true,
				false, false, false, true, false,
				false, false, false, false, false,
				false, false, false, false, false }),
			2, "неверно определены простые числа от 100 до 120")) {
			return;
		}
	}

	// Тест 3: в диапазоне 14..16 нет простых чисел.
	{
		AlgorithmData data;
		data.startNumber = 14;
		data.endNumber = 16;
		data.spiralGrid = {
			{ 14, 15, 16 },
			{ 0, 0, 0 },
			{ 0, 0, 0 }
		};
		primeSieve.MarkPrimesInSpiral(data);

		if (!check(checkPrimeMask(data,
			{ false, false, false,
				false, false, false,
				false, false, false }),
			3, "составное число ошибочно определено как простое")) {
			return;
		}
	}

	// Тест 4: построение спирали 1..9 и подсчёт простых чисел в ней.
	{
		AlgorithmData data;
		data.startNumber = 1;
		data.endNumber = 9;
		numberGeneration.GenerateDataForSpiral(data);
		primeSieve.MarkPrimesInSpiral(data);

		int primeCount = 0;
		for (const auto& row : data.primeMask) {
			for (bool isPrime : row) {
				if (isPrime) {
					++primeCount;
				}
			}
		}

		const bool correctGrid = data.spiralGrid.size() == 3
			&& data.spiralGrid[1][1] == 1;
		if (!check(correctGrid && primeCount == 4,
			4, "неверно построена спираль или посчитаны простые числа")) {
			return;
		}
	}

	// Тест 5: поиск формулы f(t) = 4t^2 + 3 на строке.
	{
		AlgorithmData data;
		data.startNumber = 1;
		data.endNumber = 100;
		data.spiralGrid = {
			{ 3, 7, 19, 39, 67 },
			{ 100, 100, 100, 100, 100 },
			{ 100, 100, 100, 100, 100 },
			{ 100, 100, 100, 100, 100 },
			{ 100, 100, 100, 100, 100 }
		};
		data.primeMask = {
			{ true, true, true, false, true },
			{ false, false, false, false, false },
			{ false, false, false, false, false },
			{ false, false, false, false, false },
			{ false, false, false, false, false }
		};

		lineAnalysis.FindRichLines(data);

		bool formulaFound = false;
		for (const LineInfo& line : data.richLines) {
			if (line.a == 4 && line.b == 0 && line.c == 3
				&& line.length == 5 && line.primeCount == 4
				&& std::abs(line.primeShare - 0.8) < 0.000001
				&& line.direction == 0) {
				formulaFound = true;
				break;
			}
		}

		if (!check(formulaFound,
			5, "не найдена формула 4t^2 + 3 с правильной статистикой")) {
			return;
		}
	}

	std::cout << "\n  Все 5 тестов пройдены успешно.\n";
}

