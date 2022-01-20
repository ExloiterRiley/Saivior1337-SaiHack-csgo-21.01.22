#include "CBaseEntity.h"

DWORD LocalPlayer::getLocalBase()
{
	return mem->read<DWORD>(G.client_dll + OFF.dwLocalPlayer); 
}

DWORD LocalPlayer::getClientState()
{
	return mem->read<DWORD>(G.engine_dll + OFF.dwClientState); 
}

DWORD LocalPlayer::getGlowObjects()
{
	return mem->read<DWORD>(G.client_dll + OFF.dwGlow); 
}

DWORD LocalPlayer::getLocalWeaponHandle()
{
	return mem->read<DWORD>(LocalPlayer::getLocalBase() + OFF.m_hActiveWeapon); 
}

DWORD LocalPlayer::getLocalCurrentWeapon()
{
	int getWeaponHandle = LocalPlayer::getLocalWeaponHandle() & 0xFFF; 
	return mem->read<DWORD>(G.client_dll + OFF.dwEntityList + (getWeaponHandle - 1) * 0x10); 
}

D3DXMATRIX LocalPlayer::getLocalViewMatrix()
{
	return mem->read<D3DXMATRIX>(G.client_dll + OFF.dwViewMatrix); 
}

D3DXVECTOR3 LocalPlayer::getLocalPos()
{
	return mem->read<D3DXVECTOR3>(LocalPlayer::getLocalBase() + OFF.m_vecOrigin); 
}

D3DXVECTOR3 LocalPlayer::getLocalViewAngles()
{
	return mem->read<D3DXVECTOR3>(LocalPlayer::getClientState() + OFF.dwClientState_ViewAngles); 
}

D3DXVECTOR3 LocalPlayer::getLocalPunchAngles()
{
	return mem->read<D3DXVECTOR3>(LocalPlayer::getLocalBase() + OFF.m_aimPunchAngle); 
}

D3DXVECTOR3 LocalPlayer::getLocalVelocity()
{
	return mem->read<D3DXVECTOR3>(LocalPlayer::getLocalBase() + OFF.m_vecVelocity); 
}

int LocalPlayer::getLocalFlags()
{
	return mem->read<int>(LocalPlayer::getLocalBase() + OFF.m_fFlags); 
}

int LocalPlayer::getLocalTeam()
{
	return mem->read<int>(LocalPlayer::getLocalBase() + OFF.m_iTeamNum); 
}

int LocalPlayer::isLocalScoped()
{
	return mem->read<int>(LocalPlayer::getLocalBase() + OFF.m_bIsScoped); 
}

int LocalPlayer::getLocalCrosshairId()
{
	return mem->read<int>(LocalPlayer::getLocalBase() + OFF.m_iCrosshairId); 
}

int LocalPlayer::getLocalActiveWeapon()
{
	return mem->read<int>(LocalPlayer::getLocalCurrentWeapon() + OFF.m_iItemDefinitionIndex); 
}

int LocalPlayer::getLocalHealth()
{
	return mem->read<int>(LocalPlayer::getLocalBase() + OFF.m_iHealth); 
}

float LocalPlayer::getLocalFlashDuration()
{
	return mem->read<float>(LocalPlayer::getLocalBase() + OFF.m_flFlashDuration); 
}

float LocalPlayer::getLocalFlashAlpha()
{
	return mem->read<float>(LocalPlayer::getLocalBase() + OFF.m_flFlashMaxAlpha); 
}

float LocalPlayer::getLocalSpeed()
{
	Vec3 Velocity = mem->read<Vec3>(LocalPlayer::getLocalBase() + OFF.m_vecVelocity); 
	return sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y); 
}

bool LocalPlayer::isInGame()
{
	int getGameState = mem->read<int>(LocalPlayer::getClientState() + OFF.m_vecViewOffset); 
	if (getGameState == 6)
		return true;
	else
		return false;
}

bool LocalPlayer::isPlayerMoving()
{
	D3DXVECTOR3 Velocity = LocalPlayer::getLocalVelocity(); 
	float isMoving = Velocity.x + Velocity.y + Velocity.z; 
	if (isMoving != 0.0f)
		return true;
	else
		return false;
}

bool LocalPlayer::isBombPlanted()
{
	return mem->read<bool>(mem->read<DWORD>(G.client_dll + OFF.dwGameRulesProxy) + OFF.m_bBombPlanted); 
}

void LocalPlayer::setLocalViewAngles(D3DXVECTOR3 angles)
{
	mem->write<D3DXVECTOR3>(LocalPlayer::getClientState() + OFF.dwClientState_ViewAngles, angles); 
}

const char* LocalPlayer::getMapName()
{
	DWORD clientState = LocalPlayer::getClientState(); 
	static std::array<char, 0x80> mapName = mem->read<std::array<char, 0x80>>(clientState + OFF.dwClientState_Map); 
	return mapName.data(); 
}

const char* LocalPlayer::getGameDirectory()
{
	DWORD clientState = LocalPlayer::getClientState(); 
	static std::array<char, 0x120> gameDirectory = mem->read<std::array<char, 0x120>>(G.engine_dll + OFF.dwGameDir); 
	return gameDirectory.data(); 
}

const char* LocalPlayer::getMapDirectory()
{
	DWORD clientState = LocalPlayer::getClientState(); 
	static std::array<char, 0x120> mapDirectory = mem->read<std::array<char, 0x120>>(clientState + OFF.dwClientState_MapDirectory); 
	return mapDirectory.data(); 
}


player_info_t LocalPlayer::getPlayerName()
{
	uintptr_t UserInfoTable = mem->read<uintptr_t>(LocalPlayer::getClientState() + OFF.dwClientState_PlayerInfo); 
	uintptr_t x = mem->read<uintptr_t>(mem->read<uintptr_t>(UserInfoTable + 0x40) + 0xC); 
	return mem->read<player_info_t>(mem->read<uintptr_t>(x + 0x28 + 0x34 * 0)); 
}

DWORD Entity::getEntityBase(int index)
{
	return mem->read<DWORD>(G.client_dll + OFF.dwEntityList + (index * 0x10)); 
}

DWORD Entity::getEntityBoneMatrix(DWORD entity)
{
	return mem->read<DWORD>(entity + OFF.m_dwBoneMatrix); 
}


D3DXVECTOR3 Entity::getEntityBonePos(DWORD entity, int boneID)
{
	Matrix3x4_t boneMatrix = mem->read<Matrix3x4_t>(Entity::getEntityBoneMatrix(entity) + boneID * 0x30); 

	return{
		boneMatrix.Matrix[0][3],
		boneMatrix.Matrix[1][3],
		boneMatrix.Matrix[2][3]
	};
}

D3DXVECTOR3 Entity::getEntityPos(DWORD entity)
{
	return mem->read<D3DXVECTOR3>(entity + OFF.m_vecOrigin); 
}

int Entity::getEntityTeam(DWORD entity)
{
	return mem->read<int>(entity + OFF.m_iTeamNum); 
}

int Entity::getEntityHealth(DWORD entity)
{
	return mem->read<int>(entity + OFF.m_iHealth);
}

int Entity::getClassID(DWORD entity)
{
	DWORD dwClientNetworkable = mem->read<DWORD>(entity + 0x8);
	DWORD dwGetClientClassFn = mem->read<DWORD>(dwClientNetworkable + 2 * 0x4);
	DWORD dwEntityClientClass = mem->read<DWORD>(dwGetClientClassFn + 1);
	return mem->read<int>(dwEntityClientClass + 20);
}

int Entity::getGlowIndex(DWORD entity)
{
	return mem->read<int>(entity + OFF.m_iGlowIndex);
}

bool Entity::isEntityHasImmunity(DWORD entity)
{
	return mem->read<bool>(entity + OFF.m_bGunGameImmunity); 
}

bool Entity::isEntitySpotted(DWORD entity)
{
	return mem->read<bool>(entity + OFF.m_bSpottedByMask); 
}

bool Entity::isEntityVisible(DWORD entity)
{
	return mem->read<bool>(entity + OFF.m_bSpotted); 
}

bool Entity::isEntityAlive(DWORD entity)
{
	if (Entity::getEntityHealth(entity) > 0 && Entity::getEntityHealth(entity) <= 100)
		return true;
	return false;
}

bool Entity::isEntityValid(DWORD entity)
{
	bool dormant = mem->read<bool>(entity + OFF.m_bDormant); 
	if ((Entity::isEntityAlive(entity) && Entity::getEntityTeam(entity) != 0) && !dormant)
		return true;
	return false;
}

player_info_t Entity::getEntityInformation(int index)
{
	uintptr_t UserInfoTable = mem->read<uintptr_t>(LocalPlayer::getClientState() + OFF.dwClientState_PlayerInfo); 
	uintptr_t x = mem->read<uintptr_t>(mem->read<uintptr_t>(UserInfoTable + 0x40) + 0xC); 
	return mem->read<player_info_t>(mem->read<uintptr_t>(x + 0x28 + 0x34 * index)); 
}