#pragma once
#include "m_headers.h"

class configurationSystem
{
public:
	void SaveConfig();
	void LoadConfig();
};

extern configurationSystem* iCFG;