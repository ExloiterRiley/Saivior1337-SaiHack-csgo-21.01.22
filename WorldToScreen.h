#pragma once
#include "m_headers.h"

class World2Screen
{
public:
	static bool ScreenTransform(const D3DXVECTOR3& point, D3DXVECTOR3& screen);
	static bool WorldToScreen(const D3DXVECTOR3& origin, D3DXVECTOR3& screen, int w, int h);
};

extern World2Screen * W2S;
