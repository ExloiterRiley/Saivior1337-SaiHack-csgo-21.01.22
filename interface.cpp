#include "interface.h"

Interfaces * con;

void Interfaces::setupConsole()
{
	SetConsoleTitle(XOR("SaiHack // By Saivior1337"));
	G.consoleWindow = GetConsoleWindow();
	G.consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetWindowRect(G.consoleWindow, &G.consoleRect);
	MoveWindow(G.consoleWindow, G.consoleRect.left, G.consoleRect.top, 600, 200, TRUE);
}

void Interfaces::ClearScreen()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi; 
	DWORD                      count; 
	DWORD                      cellCount; 
	COORD                      homeCoords = { 0, 0 }; 

	if (G.consoleHandle == INVALID_HANDLE_VALUE) return; 

	if (!GetConsoleScreenBufferInfo(G.consoleHandle, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y; 

	if (!FillConsoleOutputCharacter(G.consoleHandle, (TCHAR)' ', cellCount, homeCoords, &count)) return;

	if (!FillConsoleOutputAttribute(G.consoleHandle, csbi.wAttributes, cellCount, homeCoords, &count)) return;

	SetConsoleCursorPosition(G.consoleHandle, homeCoords);
}

void Interfaces::printColoredText(WORD color, std::string text)
{
	SetConsoleTextAttribute(G.consoleHandle, color);
	std::cout << text;
	SetConsoleTextAttribute(G.consoleHandle, 0x07);
}

void Interfaces::error_message(int errorCode)
{
	switch (errorCode)
	{
	case 0:
		con->ClearScreen();
		SetConsoleTextAttribute(G.consoleHandle, 0x4);
		std::cout << XOR("[SaiHack]: Error #0 // Failed to download offsets!") << std::endl;
		std::this_thread::sleep_for(5000ms);
		exit(0);
	case 1:
		con->ClearScreen();
		SetConsoleTextAttribute(G.consoleHandle, 0x4);
		std::cout << XOR("[SaiHack]: Error #1 // Failed to get window!") << std::endl;
		std::this_thread::sleep_for(5000ms);
		exit(0);
	case 2:
		con->ClearScreen();
		SetConsoleTextAttribute(G.consoleHandle, 0x4);
		std::cout << XOR("[SaiHack]: Error #2 // Failed to get process id!") << std::endl;
		std::this_thread::sleep_for(5000ms);
		exit(0);
	case 3:
		con->ClearScreen();
		SetConsoleTextAttribute(G.consoleHandle, 0x4);
		std::cout << XOR("[SaiHack]: Error #3 // Failed to attach process!") << std::endl;
		std::this_thread::sleep_for(5000ms);
		exit(0);
	case 4:
		con->ClearScreen();
		SetConsoleTextAttribute(G.consoleHandle, 0x4);
		std::cout << XOR("[SaiHack]: Error #4 // Failed to create configuration file!") << std::endl;
		std::this_thread::sleep_for(5000ms);
		exit(0);
	}
}

void Interfaces::terminateThread()
{
	if (GetAsyncKeyState(VK_END) & 1)
		exit(0);
}