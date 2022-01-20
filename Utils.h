#pragma once
#include "m_headers.h"

class Utils
{
public:
	DWORD GetConVarAddress(const char* name);
	UINT GetModelIndexByName(const char* modelName);
	int GetStringHash(const char* name);
	void SetValue(const char* name, float val);
	void SetValue(const char* name, int val);
	std::string getValue(const char* name);
};

extern Utils * iUtils;