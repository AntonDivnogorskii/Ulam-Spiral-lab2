#pragma once

#include <string>
#include <vector>

#include "../Domain/MenuOptions.h"
#include "../IO/ConsoleReader.h"
#include "../IO/ConsoleWriter.h"
#include "../IO/FileReader.h"
#include "../IO/FileWriter.h"
#include "../Tests/Tests.h"
#include "../Domain/AlgorithmData.h"
#include "../Core/NumberGeneration.h"
#include "../Core/PrimeSieve.h"

class Application {
public:
    int runApplication();

private:
    std::string text;
    bool running = true;

    ConsoleReader consoleReader;
    ConsoleWriter consoleWriter;
    //FileReader fileReader;
    //FileWriter fileWriter;
    
	NumberGeneration numberGeneration;
    PrimeSieve primeSieve;
    AlgorithmData algorithmData;
    Tests tests;


    void runLoginMenu();
    void runConstructionOfSpiral();
    void runResultMenu();

    int readValidatedInRange(int min, int max, const std::string& rangeErrorMessage);
};