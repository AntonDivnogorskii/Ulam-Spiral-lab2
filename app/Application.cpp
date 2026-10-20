#include "Application.h"

int Application::runApplication() {
    tests.runTests();

    consoleWriter.greetingMessage();

    while (running) {
        runLoginMenu();
    }

    return 0;
}

void Application::runLoginMenu() {
    consoleWriter.loginMenuMessage();

    userChoice = readValidatedInRange(0, 3, "• Вы можете выбрать только существующий пункт.");

    switch (static_cast<LoginMenuOption>(userChoice)) {

        case LoginMenuOption::MANUAL_INPUT:
			consoleWriter.informationMessage("• Необходимо ввести начальное число спирали");
            std::cout << "  ╰─> Введите число: ";
            algorithmData.startNumber = readValidatedInRange(1, INT_MAX, "• Введите положительное целое число.");

            consoleWriter.informationMessage("• Необходимо ввести конечное число спирали");
            std::cout << "  ╰─> Введите число: ";
            algorithmData.endNumber = readValidatedInRange(1, INT_MAX, "• Введите положительное целое число.");

            break;

        case LoginMenuOption::FILE_INPUT:
            consoleWriter.informationMessage("• Необходимо ввести путь к файлу с данными");
            std::cout << "  ╰─> Введите путь до файла: ";
            {
                std::string path;
                std::getline(std::cin, path);

                if (!fileReader.readInputData(path, algorithmData)) {
                    return;
                }
            }
            break;

        case LoginMenuOption::RUN_TESTS:
            tests.runTests();
            return;

        case LoginMenuOption::EXIT:
            consoleWriter.informationMessage("• Завершение работы программы.");
            running = false;
            return;
    }

    runConstructionOfSpiral();
}

void Application::runConstructionOfSpiral() {

    numberGeneration.GenerateDataForSpiral(algorithmData);

    consoleWriter.displayDataAsSpiral(algorithmData, false);

    primeSieve.MarkPrimesInSpiral(algorithmData);

    consoleWriter.displayDataAsSpiral(algorithmData, true);
    
    lineAnalysis.FindRichLines(algorithmData);

    consoleWriter.displayRichLines(algorithmData);

    runResultMenu();
}

void Application::runResultMenu() {
    inResultMenu = true;

    while (inResultMenu && running) {

        consoleWriter.outputMenuMessage();
        userChoice = readValidatedInRange(0, 3, "• Вы можете выбрать только существующий пункт.");

        switch (static_cast<ResultMenuOption>(userChoice)) {

            case ResultMenuOption::SAVE_INPUT_DATA:
                fileWriter.saveInputData(algorithmData);
                break;

            case ResultMenuOption::SAVE_RESULTS:
                fileWriter.saveResultsToFile(algorithmData);
                break;

            case ResultMenuOption::RETURN_TO_PREVIOUS_MENU:
                inResultMenu = false;
                break;

            case ResultMenuOption::EXIT:
                running = false;
                inResultMenu = false;
                break;
        }
    }
}

int Application::readValidatedInRange(int min, int max, const std::string& rangeErrorMessage) {
    int value;

    do {
        value = consoleReader.getInt();

        if (value == -1) {
            consoleWriter.limitMessage("• Пожалуйста, введите целое число.");
        }
        else if (value < min || value > max) {
            consoleWriter.limitMessage(rangeErrorMessage);
        }
        else {
            return value;
        }

    } while (true);
}