#include "Misc.h"

Misc * iMisc;
#define FORCE_JUMP_BITMASK (1<<0)

HRSRC ResourceStapler = FindResource(NULL, MAKEINTRESOURCE(IDR_WAVE1), "WAVE");
HANDLE ResourceStaplerHandle = LoadResource(NULL, ResourceStapler);
LPVOID ResourceStaplerVoid = LockResource(ResourceStaplerHandle);

HRSRC ResourceBameware = FindResource(NULL, MAKEINTRESOURCE(IDR_WAVE2), "WAVE");
HANDLE ResourceBamewareHandle = LoadResource(NULL, ResourceBameware);
LPVOID ResourceBamewareVoid = LockResource(ResourceBamewareHandle);

HRSRC ResourceFatality = FindResource(NULL, MAKEINTRESOURCE(IDR_WAVE3), "WAVE");
HANDLE ResourceFatalityHandle = LoadResource(NULL, ResourceFatality);
LPVOID ResourceFatalityVoid = LockResource(ResourceFatalityHandle);

HRSRC ResourcePop = FindResource(NULL, MAKEINTRESOURCE(IDR_WAVE4), "WAVE");
HANDLE ResourcePopHandle = LoadResource(NULL, ResourcePop);
LPVOID ResourcePopVoid = LockResource(ResourcePopHandle);

HRSRC ResourcePunch = FindResource(NULL, MAKEINTRESOURCE(IDR_WAVE5), "WAVE");
HANDLE ResourcePunchHandle = LoadResource(NULL, ResourcePunch);
LPVOID ResourcePunchVoid = LockResource(ResourcePunchHandle);

HRSRC ResourceSkeet = FindResource(NULL, MAKEINTRESOURCE(IDR_WAVE6), "WAVE");
HANDLE ResourceSkeetHandle = LoadResource(NULL, ResourceSkeet);
LPVOID ResourceSkeetVoid = LockResource(ResourceSkeetHandle);

HRSRC ResourceRifk = FindResource(NULL, MAKEINTRESOURCE(IDR_WAVE7), "WAVE");
HANDLE ResourceRifkHandle = LoadResource(NULL, ResourceRifk);
LPVOID ResourceRifkVoid = LockResource(ResourceRifkHandle);

void Misc::Sound()
{
	int totalhits = mem->read<int>(LocalPlayer::getLocalBase() + 0x103f8);
	if (totalhits > CFG.hits)
	{
		CFG.hits = totalhits;
		switch (CFG.selectedSound)
		{
		case 0:
			sndPlaySound((LPCSTR)ResourceStaplerVoid, SND_MEMORY | SND_ASYNC);
			break;
		case 1:
			sndPlaySound((LPCSTR)ResourceBamewareVoid, SND_MEMORY | SND_ASYNC);
			break;
		case 2:
			sndPlaySound((LPCSTR)ResourceFatalityVoid, SND_MEMORY | SND_ASYNC);
			break;
		case 3:
			sndPlaySound((LPCSTR)ResourcePopVoid, SND_MEMORY | SND_ASYNC);
			break;
		case 4:
			sndPlaySound((LPCSTR)ResourcePunchVoid, SND_MEMORY | SND_ASYNC);
			break;
		case 5:
			sndPlaySound((LPCSTR)ResourceSkeetVoid, SND_MEMORY | SND_ASYNC);
			break;
		case 6:
			sndPlaySound((LPCSTR)ResourceRifkVoid, SND_MEMORY | SND_ASYNC);
			break;
		}

	}
	if (totalhits == 0) CFG.hits = 0;
}

int currJumpState{ 0 };
BYTE onGround = 1;

void Misc::Bunny()
{
	if (LocalPlayer::isPlayerMoving())
	{
		if (GetAsyncKeyState(VK_SPACE) < 0)
		{
			currJumpState = mem->read<DWORD>(G.client_dll + OFF.dwForceJump); 
			onGround = mem->read<BYTE>(LocalPlayer::getLocalBase() + OFF.m_fFlags); 
			if (onGround & (1 << 0))
			{
				currJumpState |= FORCE_JUMP_BITMASK; 
				mem->write<int>(G.client_dll + OFF.dwForceJump, currJumpState); 
			}
			else
			{
				currJumpState &= ~FORCE_JUMP_BITMASK; 
				mem->write<int>(G.client_dll + OFF.dwForceJump, currJumpState); 
			}
		}
	}
}