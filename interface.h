#pragma once
#include "m_headers.h"

class Interfaces
{
public:
	void setupConsole();
	void ClearScreen();
	void error_message(int errorCode);
	void printColoredText(WORD color, std::string text);
	void terminateThread();
};

extern Interfaces * con;