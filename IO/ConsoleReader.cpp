#include "ConsoleReader.h"

int ConsoleReader::getInt()
{
    int number = 0;
    std::string inputText;

    std::cin >> inputText;

    // Очистка буфера от остатков предыдущего ввода
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (inputText.empty())
        return -1;

    for (char c : inputText) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            return -1;
        }
        number = number * 10 + (c - '0');
    }

    return number;
}
