#include "Aimbot.h"

aimBot * iAimbot;


DWORD aimBot::getPlayer()
{
	D3DXVECTOR3 w2sHead;

	DWORD playerToAim = NULL;
	double lowestDistance = 500;

	for (int i = 1; i < 64; i++)
	{
		auto base = Entity::getEntityBase(i); 

		if (base != NULL)
		{

			if (Entity::getEntityTeam(base) != LocalPlayer::getLocalTeam() && Entity::isEntityValid(base) && !Entity::isEntityHasImmunity(base))
			{
				W2S->WorldToScreen(Entity::getEntityBonePos(base, 8), w2sHead, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)); 

				double dist = sqrt(pow((GetSystemMetrics(SM_CXSCREEN) / 2) - w2sHead.x, 2) + pow((GetSystemMetrics(SM_CYSCREEN) / 2) - w2sHead.y, 2)); 

				if (dist < lowestDistance)
				{
					lowestDistance = dist; 
					playerToAim = base; 
				}
			}
		}
	}
	return playerToAim;
}

void aimBot::Aim(DWORD closetEnemy, DWORD entity)
{
	float null[3] = { 0.f, 0.f, 0.f };
	switch (CFG.selectedBone)
	{
	case 0:
		CFG.aimBone = 8;
		break;
	case 1:
		CFG.aimBone = 7;
		break;
	case 2:
		CFG.aimBone = 4;
		break;
	}

	if (closetEnemy != NULL)
	{
		if (LocalPlayer::getLocalTeam() != Entity::getEntityTeam(entity))
		{
			float fFov = iMath->GetFOV(LocalPlayer::getLocalViewAngles(), LocalPlayer::getLocalPos(), Entity::getEntityPos(closetEnemy));
			if ((fFov <= CFG.aimFov) && Entity::getEntityHealth(entity) >= 1)
			{
				D3DXVECTOR3 localpos = LocalPlayer::getLocalPos();
				localpos.z += mem->read<float>(LocalPlayer::getLocalBase() + OFF.m_vecViewOffset + 0x8);
				D3DXVECTOR3 enemycoords = Entity::getEntityBonePos(closetEnemy, CFG.aimBone);
				D3DXVECTOR3 newanglez = iMath->CalcAngle(localpos, enemycoords, true ? LocalPlayer::getLocalPunchAngles() : null);
				D3DXVECTOR3 delta = iMath->ClampAngle(newanglez - LocalPlayer::getLocalViewAngles());
				newanglez = LocalPlayer::getLocalViewAngles() + delta / CFG.aimSmooth;
				newanglez = iMath->ClampAngle(newanglez);



				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && LocalPlayer::getLocalActiveWeapon() != 41 && LocalPlayer::getLocalActiveWeapon() != 42 && LocalPlayer::getLocalActiveWeapon() != 43 && LocalPlayer::getLocalActiveWeapon() != 44 && LocalPlayer::getLocalActiveWeapon() != 45 && LocalPlayer::getLocalActiveWeapon() != 46 && LocalPlayer::getLocalActiveWeapon() != 47 && LocalPlayer::getLocalActiveWeapon() != 48 && LocalPlayer::getLocalActiveWeapon() != 49 && LocalPlayer::getLocalActiveWeapon() != 59)
				{
					if (!isnan(newanglez.x) && !isnan(newanglez.y))
					{
						switch (CFG.aimVisibleCheck)
						{
						case TRUE:
							if (Entity::isEntitySpotted(closetEnemy))
							{
								LocalPlayer::setLocalViewAngles(newanglez);
							}
							break;
						case FALSE:
							if (Entity::isEntitySpotted(closetEnemy) || !Entity::isEntitySpotted(closetEnemy))
							{
								LocalPlayer::setLocalViewAngles(newanglez);
							}
							break;
						}
					}
				}
			}
		}
	}
}

void aimBot::Trigger()
{
	int crosshair = LocalPlayer::getLocalCrosshairId(); 
	if (crosshair != 0 && crosshair < 64)
	{
		DWORD entity = mem->read<DWORD>(G.client_dll + OFF.dwEntityList + ((crosshair - 1) * 0x10)); 
		if (entity != NULL)
		{
			if (Entity::isEntityValid(entity) && !Entity::isEntityHasImmunity(entity))
			{
				if (LocalPlayer::getLocalTeam() != Entity::getEntityTeam(entity) && !Entity::isEntityHasImmunity(entity))
				{
					if (LocalPlayer::getLocalActiveWeapon() != 41 && LocalPlayer::getLocalActiveWeapon() != 42 && LocalPlayer::getLocalActiveWeapon() != 43 && LocalPlayer::getLocalActiveWeapon() != 44 && LocalPlayer::getLocalActiveWeapon() != 45 && LocalPlayer::getLocalActiveWeapon() != 46 && LocalPlayer::getLocalActiveWeapon() != 47 && LocalPlayer::getLocalActiveWeapon() != 48 && LocalPlayer::getLocalActiveWeapon() != 49 && LocalPlayer::getLocalActiveWeapon() != 59)
					{
						mem->write<int>(G.client_dll + OFF.dwForceAttack, 5);
						std::this_thread::sleep_for(20ms);
						mem->write<int>(G.client_dll + OFF.dwForceAttack, 4);
					}
				}
			}
		}
	}
}
