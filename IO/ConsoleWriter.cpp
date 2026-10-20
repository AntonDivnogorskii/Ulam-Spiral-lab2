#include "ConsoleWriter.h"

void ConsoleWriter::greetingMessage()
{
    std::cout << std::endl;
    std::cout << "  ╔" << std::string(70, '=') << "╗\n";
    std::cout << "  ║ ИНСТИТУТ:                                                            ║\n";
    std::cout << "  ║  • СПбГТИ(ТУ)                                                        ║\n";
    std::cout << "  ║                                                                      ║\n";
    std::cout << "  ║ ГРУППА:                                                              ║\n";
    std::cout << "  ║  • 433                                                               ║\n";
    std::cout << "  ║                                                                      ║\n";
    std::cout << "  ║ КОМАНДА РАЗРАБОТЧИКОВ:                                               ║\n";
    std::cout << "  ║  • Дивногорский Антон Андреевич                                      ║\n";
    std::cout << "  ║  • Иванов Глеб Игоревич                                              ║\n";
    std::cout << "  ║  • Панина Дарья Данииловна                                           ║\n";
    std::cout << "  ║                                                                      ║\n";
    std::cout << "  ║ ТЕКСТ ЗАДАНИЯ:                                                       ║\n";
    std::cout << "  ║  • Напишите программу, которая отображает целые числа на плоскость   ║\n";
    std::cout << "  ║    некоторым регулярным образом и отмечает на рисунке места, где     ║\n";
    std::cout << "  ║    находятся простые числа. Выведите формулы, описывающие прямые     ║\n";
    std::cout << "  ║    линии на вашем рисунке, и напечатайте те из них, которые особенно ║\n";
    std::cout << "  ║    изобилуют простыми числами; печатайте также долю простых чисел на ║\n";
    std::cout << "  ║    этих прямых.                                                      ║\n";
    std::cout << "  ╚" << std::string(70, '=') << "╝\n";
}

void ConsoleWriter::loginMenuMessage()
{
    std::cout << std::endl;
    std::cout << "  ┌─────────────────── МЕНЮ ───────────────────┐\n";
    std::cout << "    [0] Завершить выполнение программы \n";
    std::cout << "    [1] Ввести данные с клавиатуры \n";
    std::cout << "    [2] Загрузить данные из файла \n";
    std::cout << "    [3] Запустить тесты \n";
    std::cout << "  └────────────────────────────────────────────┘\n\n";
    std::cout << "  ╰─> Выберите пункт: ";
}

void ConsoleWriter::outputMenuMessage()
{
    std::cout << std::endl;
    std::cout << "  ┌─────────────────── МЕНЮ ───────────────────┐\n";
    std::cout << "    [0] Завершить выполнение программы \n";
    std::cout << "    [4] Сохранить исходный текст в файл \n";
    std::cout << "    [5] Сохранить результаты в файл \n";
    std::cout << "    [6] Вернуться к предыдущему меню \n";
    std::cout << "  └────────────────────────────────────────────┘\n\n";
    std::cout << "  ╰─> Выберите пункт: ";
}

void ConsoleWriter::limitMessage(const std::string& message)
{
    std::cout << std::endl;
    std::cout << "  ┌────────────────── >< ОГРАНИЧЕНИЕ ──────────────────┐\n";
    std::cout << "    " << message << "\n";
    std::cout << "  └────────────────────────────────────────────────────┘\n\n";
    std::cout << "  ╰─> Выберите пункт: ";
}

void ConsoleWriter::warningMessage(const std::string& message)
{
    std::cout << std::endl;
    std::cout << "  ┌────────────────── ! ПРЕДУПРЕЖДЕНИЕ ──────────────────┐\n";
    std::cout << "    " << message << "\n";
    std::cout << "  └──────────────────────────────────────────────────────┘\n\n";
}


void ConsoleWriter::errorMessage(const std::string& message)
{
    std::cout << std::endl;
    std::cout << "  ┌────────────────── X ОШИБКА ──────────────────┐\n";
    std::cout << "    " << message << "\n";
    std::cout << "  └──────────────────────────────────────────────┘\n\n";
}

void ConsoleWriter::informationMessage(const std::string& message)
{
    std::cout << std::endl;
    std::cout << "  ┌───────────────── ? ИНФОРМАЦИЯ ───────────────────┐\n";
    std::cout << "    " << message << "\n";
    std::cout << "  └──────────────────────────────────────────────────┘\n\n";
}

void ConsoleWriter::successMessage(const std::string& message)
{
    std::cout << std::endl;
    std::cout << "  ┌──────────────────── УСПЕХ ────────────────────┐\n";
    std::cout << "    " << message << "\n";
    std::cout << "  └───────────────────────────────────────────────┘\n\n";
}

void ConsoleWriter::displayDataAsSpiral(const AlgorithmData& algorithmData, bool highlightPrimes) {
    
    // Шапка
    std::cout << std::endl;

    if (highlightPrimes) {
		std::cout << "  СПИРАЛЬ С ПРОСТЫМИ ЧИСЛАМИ: \n";
    }
    else {
        std::cout << "  СПИРАЛЬ: \n";
    }

    // Сторона спирали
    const int side = static_cast<int>(algorithmData.spiralGrid.size());

    // Ширина под цифры = количество цифр в самом большом числе
    const size_t digitsWidth = std::to_string(algorithmData.endNumber).length();

    // Ширина клетки: цифры + место под скобки (если простые выделяются)
    const size_t cellWidth = digitsWidth + (highlightPrimes ? 2 : 0);

    // Ширина колонки: клетка + 2 пробела отступа слева
    const int columnWidth = static_cast<int>(cellWidth) + 2;

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            const int number = algorithmData.spiralGrid[i][j];

            // Текст клетки: для пустой клетки остаётся пустым
            std::string cellText;

            // Пустая клетка (спираль закончилась раньше, чем заполнился квадрат)
            if (number != 0) {
                // Цифры, выровненные по правому краю внутри своей ширины
                std::string digits = std::to_string(number);
                digits = std::string(digitsWidth - digits.length(), ' ') + digits;

                if (highlightPrimes) {
                    // Простое: в скобках, обычное: пробелы на месте скобок,
                    // чтобы цифры стояли в одних и тех же позициях
                    if (algorithmData.primeMask[i][j]) {
                        cellText = "[" + digits + "]";
                    }
                    else {
                        cellText = " " + digits + " ";
                    }
                }
                else {
                    cellText = digits;
                }
            }

            std::cout << std::setw(columnWidth) << cellText;
        }

        std::cout << "\n\n";
    }
}
