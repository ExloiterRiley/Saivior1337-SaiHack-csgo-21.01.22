#pragma once
#include "m_headers.h"

class aimBot
{
public:
	void Aim(DWORD closetEnemy, DWORD entity);
	void Trigger();
	DWORD getPlayer();
};

extern aimBot * iAimbot;