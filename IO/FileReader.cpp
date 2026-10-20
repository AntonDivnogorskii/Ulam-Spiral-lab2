#include "FileReader.h"

bool FileReader::readInputData(const std::string& filename, AlgorithmData& algorithmData)
{
	const std::string pathText = trimCopy(filename);
	const std::filesystem::path path = pathFromUtf8(pathText);
	std::ifstream file(path);

	if (!file.is_open()) {
		consoleWriter.errorMessage("• Не удалось открыть файл по пути: \n    " + pathText);
		return false;
	}

	int startNumber = 0;
	int endNumber = 0;

	if (!(file >> startNumber >> endNumber)) {
		consoleWriter.warningMessage("• Файл пуст или не содержит двух целых чисел.");
		return false;
	}

	if (startNumber <= 0 || endNumber <= 0 || startNumber > endNumber) {
		consoleWriter.warningMessage("• Файл содержит некорректный диапазон чисел.");
		return false;
	}

	algorithmData.startNumber = startNumber;
	algorithmData.endNumber = endNumber;
	consoleWriter.successMessage("• Исходный диапазон загружен из файла.");
	return true;
}

std::filesystem::path FileReader::pathFromUtf8(const std::string& value)
{
	const auto* first = reinterpret_cast<const char8_t*>(value.data());
	return std::filesystem::path(std::u8string(first, first + value.size()));
}

std::string FileReader::trimCopy(std::string value)
{
	const auto first = value.find_first_not_of(" \t\r\n");
	if (first == std::string::npos) {
		return {};
	}

	const auto last = value.find_last_not_of(" \t\r\n");
	value = value.substr(first, last - first + 1);

	if (value.size() >= 2 && ((value.front() == '"' && value.back() == '"')
		|| (value.front() == '\'' && value.back() == '\''))) {
		value = value.substr(1, value.size() - 2);
		const auto innerFirst = value.find_first_not_of(" \t\r\n");
		const auto innerLast = value.find_last_not_of(" \t\r\n");
		value = innerFirst == std::string::npos
			? std::string{}
			: value.substr(innerFirst, innerLast - innerFirst + 1);
	}

	return value;
}

