#include "Models.h"

Models * iModels;

unsigned long __stdcall Models::SetKnife(void*)
{
	int knifeIndex; 
	int gmibncounter = 1000; 
	int knifeID;
	const char* modelName = "";
	while (true)
	{
		if (CFG.models)
		{
			switch (CFG.selectedModels)
			{
			case 0:
				modelName = "models/weapons/v_knife_m9_bay.mdl";
				knifeIndex = 508;
				break;
			case 1:
				modelName = "models/weapons/v_knife_karam.mdl";
				knifeIndex = 507;
				break;
			case 2:
				modelName = "models/weapons/v_knife_flip.mdl";
				knifeIndex = 505;
				break;
			case 3:
				modelName = "models/weapons/v_knife_ghost.mdl";
				knifeIndex = 505;
				break;
			case 4:
				modelName = "models/weapons/v_knife_gut.mdl";
				knifeIndex = 506;
				break;
			}


			gmibncounter++; 
			if (gmibncounter >= 1000)
			{
				knifeID = iUtils->GetModelIndexByName(modelName); 
				gmibncounter = 0; 
			}


			for (int i = 0; i < 8; i++)
			{
				WORD WeaponEnt = mem->read<int>(LocalPlayer::getLocalBase() + OFF.m_hMyWeapons + i * 0x4) & 0xFFF; 
				int Weapon = mem->read<int>((int)G.client_dll + OFF.dwEntityList + (WeaponEnt - 1) * 0x10); 
				if (Weapon == 0)
				{
					continue; 
				}
				short WeaponID = mem->read<short>(Weapon + OFF.m_iItemDefinitionIndex); 

				switch (WeaponID)
				{
				case 0:
					continue;
					break;
				case 42:
				case 59:
					mem->write<WORD>(Weapon + OFF.m_iItemDefinitionIndex, knifeIndex); 
					break;
				}

			}

			short mywepID = mem->read<short>(LocalPlayer::getLocalBase() + OFF.m_hActiveWeapon) & 0xFFF; 
			short weaponIndex = mem->read<short>(mem->read<DWORD>(G.client_dll + OFF.dwEntityList + (mywepID - 1) * 0x10) + OFF.m_iItemDefinitionIndex); 
			if (weaponIndex == knifeIndex)
			{
				short activeViewModel = mem->read<short>(LocalPlayer::getLocalBase() + OFF.m_hViewModel) & 0xfff; 
				DWORD activeViewModelBase = mem->read<DWORD>(G.client_dll + OFF.dwEntityList + (activeViewModel - 1) * 0x10); 
				mem->write<UINT>(activeViewModelBase + 0x258, knifeID); 

			}
			mem->write<int>(G.engine_dll + 0x174, -1);
		}
		else
		{
			std::this_thread::sleep_for(2000ms);
		}
	}
}