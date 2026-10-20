#pragma once

#include <filesystem>
#include <string>
#include <fstream>

#include "../Domain/AlgorithmData.h"
#include "ConsoleWriter.h"

class FileReader {
public:
	bool readInputData(const std::string& filename, AlgorithmData& algorithmData);

private:
	ConsoleWriter consoleWriter;

	static std::filesystem::path pathFromUtf8(const std::string& value);
	static std::string trimCopy(std::string value);
};
