#include "FileWriter.h"

void FileWriter::saveInputData(const AlgorithmData& algorithmData)
{
	std::ostringstream content;
	content << algorithmData.startNumber << " " << algorithmData.endNumber;

	saveContent(content.str(),
		"\n  ╰─> Введите путь к файлу для сохранения исходного диапазона: ",
		"• Исходный диапазон сохранён в файл.",
		"• Файл создан и исходный диапазон сохранён.",
		"• Исходный диапазон сохранён в новый файл.");
}

void FileWriter::saveResultsToFile(const AlgorithmData& algorithmData)
{
	saveContent(buildResultsContent(algorithmData),
		"\n  ╰─> Введите путь к файлу для сохранения результатов: ",
		"• Результаты перезаписаны в файл.",
		"• Файл создан и результаты сохранены.",
		"• Результаты сохранены в новый файл.");
}

void FileWriter::saveContent(const std::string& content,
	const std::string& prompt,
	const std::string& savedMessage,
	const std::string& createdMessage,
	const std::string& newFileMessage)
{
	std::string rawPath;
	std::cout << prompt;
	std::getline(std::cin, rawPath);
	rawPath = trimCopy(rawPath);

	const std::filesystem::path path = pathFromUtf8(rawPath);
	std::error_code ec;

	if (std::filesystem::exists(path, ec)) {
		std::ofstream test(path, std::ios::app);
		if (!test) {
			consoleWriter.warningMessage("• Файл доступен только для чтения или недоступен для записи");
			return;
		}
		test.close();

		const auto fileSize = std::filesystem::file_size(path, ec);
		if (!ec && fileSize > 0) {
			consoleWriter.informationMessage("• Файл содержит данные. Перезаписать? (y/n)");
			std::cout << "  ╰─> ";
			std::string answer;
			std::getline(std::cin, answer);

			if (!isYes(answer)) {
				consoleWriter.informationMessage("• Исходные данные не перезаписаны.");
				return;
			}
		}

		if (!writeContent(path, content)) {
			consoleWriter.errorMessage("• Не удалось открыть файл для записи.");
			return;
		}
		consoleWriter.successMessage(savedMessage);
		return;
	}

	consoleWriter.warningMessage("• Файл не существует. Создать файл? (y/n)");
	std::cout << "  ╰─> ";
	std::string answer;
	std::getline(std::cin, answer);

	if (!isYes(answer)) {
		consoleWriter.informationMessage("• Создание файла отменено.");
		return;
	}

	if (writeContent(path, content)) {
		consoleWriter.successMessage(createdMessage);
		return;
	}

	consoleWriter.warningMessage("• Невозможно создать файл по указанному пути");
	std::cout << "\n  ╰─> Введите другой путь или нажмите Enter для отмены: ";
	std::string newPath;
	std::getline(std::cin, newPath);
	newPath = trimCopy(newPath);

	if (newPath.empty()) {
		std::cout << "Отмена.\n";
		return;
	}

	const std::filesystem::path alternativePath = pathFromUtf8(newPath);
	if (!writeContent(alternativePath, content)) {
		consoleWriter.errorMessage("• Не удалось создать второй файл.");
		return;
	}
	consoleWriter.successMessage(newFileMessage);
}

bool FileWriter::writeContent(const std::filesystem::path& path, const std::string& content)
{
	std::ofstream output(path, std::ios::binary | std::ios::trunc);
	if (!output) {
		return false;
	}

	output << content;
	return static_cast<bool>(output);
}

std::string FileWriter::buildResultsContent(const AlgorithmData& algorithmData) const
{
	std::ostringstream output;
	output << "ИСХОДНЫЙ ДИАПАЗОН: " << algorithmData.startNumber
		<< ".." << algorithmData.endNumber << "\n\n";
	output << buildSpiral(algorithmData, false);
	output << buildSpiral(algorithmData, true);

	static const char* directionNames[] = {
		"по строке (вправо)",
		"по столбцу (вниз)",
		"по диагонали (вниз-вправо)",
		"по диагонали (вниз-влево)"
	};

	output << std::fixed << std::setprecision(1);
	output << "Средняя доля простых чисел в спирали: "
		<< algorithmData.overallPrimeShare * 100 << "%\n";

	if (algorithmData.richLines.empty()) {
		output << "Линий с повышенной долей простых чисел не найдено.\n";
	}
	else {
		output << "Линии с повышенной долей простых чисел:\n\n";
	}

	for (const LineInfo& line : algorithmData.richLines) {
		std::string formula = std::to_string(line.a) + "t^2";
		formula += (line.b >= 0 ? " + " : " - ") + std::to_string(std::abs(line.b)) + "t";
		formula += (line.c >= 0 ? " + " : " - ") + std::to_string(std::abs(line.c));

		const int direction = (line.direction >= 0 && line.direction < 4) ? line.direction : 0;
		output << "f(t) = " << formula << "\n"
			<< "    " << directionNames[direction]
			<< ", t = 0.." << line.length - 1
			<< ", простых: " << line.primeCount << " из " << line.length
			<< " (" << line.primeShare * 100 << "%)\n\n";
	}

	return output.str();
}

std::string FileWriter::buildSpiral(const AlgorithmData& algorithmData, bool highlightPrimes) const
{
	std::ostringstream output;
	output << (highlightPrimes ? "СПИРАЛЬ С ПРОСТЫМИ ЧИСЛАМИ:\n" : "СПИРАЛЬ:\n");

	const size_t digitsWidth = std::to_string(algorithmData.endNumber).length();
	const int columnWidth = static_cast<int>(digitsWidth + (highlightPrimes ? 2 : 0)) + 2;
	const int side = static_cast<int>(algorithmData.spiralGrid.size());

	for (int i = 0; i < side; ++i) {
		for (int j = 0; j < side; ++j) {
			const int number = algorithmData.spiralGrid[i][j];
			std::string cellText;

			if (number != 0) {
				std::string digits = std::to_string(number);
				digits = std::string(digitsWidth - digits.length(), ' ') + digits;
				if (highlightPrimes) {
					const bool isPrime = i < static_cast<int>(algorithmData.primeMask.size())
						&& j < static_cast<int>(algorithmData.primeMask[i].size())
						&& algorithmData.primeMask[i][j];
					cellText = isPrime ? "[" + digits + "]" : " " + digits + " ";
				}
				else {
					cellText = digits;
				}
			}

			output << std::setw(columnWidth) << cellText;
		}
		output << "\n\n";
	}
	output << "\n";
	return output.str();
}

std::string FileWriter::trimCopy(std::string value)
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
		value = innerFirst == std::string::npos ? std::string{} : value.substr(innerFirst, innerLast - innerFirst + 1);
	}
	return value;
}

std::filesystem::path FileWriter::pathFromUtf8(const std::string& value)
{
	const auto* first = reinterpret_cast<const char8_t*>(value.data());
	return std::filesystem::path(std::u8string(first, first + value.size()));
}

bool FileWriter::isYes(const std::string& answer)
{
	return answer == "y" || answer == "Y" || answer == "д" || answer == "Д";
}
