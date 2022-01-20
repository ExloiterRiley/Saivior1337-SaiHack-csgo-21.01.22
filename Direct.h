#pragma once
#include "m_headers.h"

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class directX
{
public:
	static unsigned long __stdcall CreateDirectWindow(void*);
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void ResetDevice();
};

extern directX* d3d;