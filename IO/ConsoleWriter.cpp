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

void ConsoleWriter::displayDataAsSpiral(const AlgorithmData& algorithmData) {
    const int side = algorithmData.lengthOfSideOfSquare;

    // ширина колонки = количество цифр в самом длинном числе
    // (оно стоит в конце спирали, но проще найти максимум обходом)
    size_t maxLength = 0;
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            size_t length = std::to_string(algorithmData.spiralGrid[i][j]).length();

            if (length > maxLength) {
                maxLength = length;
            }
        }
    }

    // Вывод
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            std::cout << std::setw(maxLength + 2) << algorithmData.spiralGrid[i][j];
        }
        std::cout << "\n";
    }
}
