#pragma once
#include "m_headers.h"

class GlobalVars
{
public:
	HWND consoleWindow;
	HWND gameWindow;
	HANDLE consoleHandle;
	HANDLE gameHandle;
	DWORD gameProcessId;
	DWORD client_dll, engine_dll, vstdlib_dll, client_dll_size, engine_dll_size, vstdlib_dll_size;
	RECT consoleRect;
};

class CheatOffsets
{
public:
	DWORD dwLocalPlayer;
	DWORD dwEntityList;
	DWORD dwGlow;
	DWORD dwForceJump;
	DWORD dwForceAttack;
	DWORD dwWorld, dwClasses, totalHitsOnServer, nModelIndex, ClientCMD;
	DWORD m_iGlowIndex, m_vecOrigin, m_vecViewOffset, m_viewPunchAngle, m_iFOV, m_iFOVStart, m_hActiveWeapon, dwClientState_MapDirectory;
	DWORD m_dwBoneMatrix, m_clrRender, m_aimPunchAngle, m_aimPunchAngleVel, m_hMyWeapons;
	DWORD dwClientState, dwClientState_ViewAngles, dwRadarBase, m_bDormant, dwClientState_PlayerInfo, dwClientState_Map, dwGameDir;
	DWORD m_bSpotted, m_bSpottedByMask, m_fFlags, m_iCrosshairId, dwViewMatrix, model_ambient_min, m_hViewModel;
	DWORD m_iHealth, m_iTeamNum, m_vecVelocity, m_bIsDefusing, m_iItemDefinitionIndex, m_bIsScoped, m_flFlashMaxAlpha, m_bGunGameImmunity, m_ArmorValue, dwGameRulesProxy, m_bBombPlanted, m_nViewModelIndex;
	DWORD m_iItemIDHigh, m_OriginalOwnerXuidLow, m_OriginalOwnerXuidHigh, m_nFallbackPaintKit, m_nFallbackSeed, m_nFallbackStatTrak, m_flFallbackWear, m_szCustomName, m_iEntityQuality, m_flFlashDuration, m_bInReload;
	DWORD clientstate_delta_ticks;
};

class Config
{
public:
	bool radar = false;
	bool glow = false;
	bool glowFriends = false;
	bool clrRender = false;
	bool hitSound = false;
	bool bunnyHop = false;
	bool AimBotB = false;
	bool triggerBot = false;
	bool aimVisibleCheck = true;
	bool models = false;
	bool shouldExit = false;
	int menuTabs;
	int selectedGlowStyle = 0;
	int selectedGlowFriendStyle = 0;
	int selectedSound = 0;
	int selectedBone = 0;
	int selectedModels = 0;
	int hits = 0;
	int aimSmooth = 1;
	int aimBone;
	float glowColor[4] = { 1.f, 1.f, 1.f, 0.5f };
	float glowFriendColor[4] = { 1.f, 1.f, 1.f, 0.5f };
	float clrRenderColor[3] = {1.f, 1.f, 1.f};
	float clrRenderFriendColor[3] = { 1.f, 1.f, 1.f };
	float aimFov = 0.f;
};

extern GlobalVars G;
extern CheatOffsets OFF;
extern Config CFG;