#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "../Domain/AlgorithmData.h"

class ConsoleWriter {
public:
    void greetingMessage();
    void loginMenuMessage();
    void outputMenuMessage();

    void displayDataAsSpiral(const AlgorithmData& algorithmData);

    void limitMessage(const std::string& message);
    void warningMessage(const std::string& message);
    void errorMessage(const std::string& message);
    void informationMessage(const std::string& message);
    void successMessage(const std::string& message);
};