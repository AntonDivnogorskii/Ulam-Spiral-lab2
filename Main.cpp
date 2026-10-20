#include <Windows.h>

#include "app/Application.h"

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Application app;
	app.runApplication();

	return 0;
}