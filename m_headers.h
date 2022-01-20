#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <TlHelp32.h>
#include <thread>
#include <chrono>
#include <urlmon.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <intrin.h>
#include <corecrt_math_defines.h>

#include "m_globals.h"
#include "interface.h"
#include "GetOffsets.h"
#include "ProcessMemory.h"
#include "Direct.h"
#include "CBaseEntity.h"
#include "Visuals.h"
#include "configurationSystem.h"
#include "Misc.h"
#include "Aimbot.h"
#include "Models.h"
#include "Utils.h"
#include "Math.h"
#include "WorldToScreen.h"
#include "xorstr.h"
#include "json.h"
#include "resource.h"

#include "img/imgui.h"
#include "img/imgui_impl_dx9.h"
#include "img/imgui_impl_win32.h"

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib,"winmm.lib")

using namespace std::chrono_literals;
using json = nlohmann::json;