#pragma once

#include <filesystem>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../Domain/AlgorithmData.h"
#include "ConsoleWriter.h"

class FileWriter {
public:
	void saveInputData(const AlgorithmData& algorithmData);
	void saveResultsToFile(const AlgorithmData& algorithmData);

private:
	ConsoleWriter consoleWriter;

	void saveContent(const std::string& content,
		const std::string& prompt,
		const std::string& savedMessage,
		const std::string& createdMessage,
		const std::string& newFileMessage);
	bool writeContent(const std::filesystem::path& path, const std::string& content);
	std::string buildResultsContent(const AlgorithmData& algorithmData) const;
	std::string buildSpiral(const AlgorithmData& algorithmData, bool highlightPrimes) const;
	static std::filesystem::path pathFromUtf8(const std::string& value);
	static std::string trimCopy(std::string value);
	static bool isYes(const std::string& answer);
};
