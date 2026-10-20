#include "Application.h"

int Application::runApplication() {
    //tests.runTests();

    consoleWriter.greetingMessage();

    while (running) {
        runLoginMenu();
    }

    return 0;
}

void Application::runLoginMenu() {
    consoleWriter.loginMenuMessage();

    int userChoice = readValidatedInRange(0, 3, "• Вы можете выбрать только существующий пункт.");

    switch (static_cast<LoginMenuOption>(userChoice)) {

        case LoginMenuOption::MANUAL_INPUT:
			consoleWriter.informationMessage("• Необходимо ввести число для начала спирали");
            std::cout << "  ╰─> Введите число: ";
            algorithmData.startNumber = readValidatedInRange(1, INT_MAX, "• Введите положительное целое число.");

            consoleWriter.informationMessage("• Необходимо ввести число для начала спирали");
            std::cout << "  ╰─> Введите число: ";
            algorithmData.lengthOfSideOfSquare = readValidatedInRange(1, INT_MAX, "• Введите положительное целое число.");

			numberGeneration.GenerateDataForSpiral(algorithmData);
            
			consoleWriter.displayDataAsSpiral(algorithmData);

            primeSieve.MarkPrimesInSpiral(algorithmData);

            break;

        case LoginMenuOption::FILE_INPUT:
            //std::string path = consoleReader.readFilePath();

            //text = fileIO.readTextFromFile(path);

            //if (text.empty()) {
            //    consoleWriter.informationMessage("• Не удалось считать текст из файла.");
            //    return;
            //}

            //break;

        case LoginMenuOption::RUN_TESTS:
            //tests.runTests();
            return;

        case LoginMenuOption::EXIT:
            consoleWriter.informationMessage("• Завершение работы программы.");
            running = false;
            return;
    }

    runResultMenu();
}

void Application::runResultMenu() {
    bool inResultMenu = true;
    //while (inResultMenu) {
    //    consoleWriter.outputMenu();
    //    int choice = readValidatedChoice(0, 6);

    //    switch (static_cast<MenuOptions>(choice)) {
    //    case MenuOptions::SAVE_TEXT:
    //        fileIO.saveTextToFile(text);
    //        break;

    //    case MenuOptions::SAVE_RESULTS:
    //        fileIO.saveResultsToFile(results);
    //        break;

    //    case MenuOptions::RETURN_TO_PREVIOUS_MENU:
    //        inResultMenu = false;
    //        break;

    //    case MenuOptions::EXIT:
    //        running = false;
    //        inResultMenu = false;
    //        break;

    //    }
    //}
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