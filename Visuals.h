#pragma once
#include "m_headers.h"

struct GlowStruct
{
	BYTE nextFreeSlot[0x4];
	BYTE entity[0x4];
	float r;
	float g;
	float b;
	float a;
	BYTE pad0[0x10];
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloomRender;
	int m_nFullBloomStencilTestValue;
	int glowStyle;
};

struct ClrRender
{
	BYTE red, green, blue;
};


class Visuals
{
public:
	GlowStruct SetGlowColor(GlowStruct Glow, DWORD entity);
	void RenderChams(DWORD entity);
	void Glow(DWORD entity);
	int InGameRadar(DWORD entity);
};

extern Visuals * iVisuals;