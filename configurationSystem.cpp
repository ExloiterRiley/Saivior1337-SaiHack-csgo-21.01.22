#include "configurationSystem.h"

configurationSystem* iCFG;

void configurationSystem::SaveConfig()
{
	std::ofstream create_config(XOR("config.ini"));
	if (!create_config)
		con->error_message(4);

	create_config << CFG.radar;
	create_config << XOR(" ") << CFG.glow << XOR(" ") << CFG.glowColor[0] << XOR(" ") << CFG.glowColor[1] << XOR(" ") << CFG.glowColor[2] << XOR(" ") << CFG.glowColor[3] << XOR(" ") << CFG.selectedGlowStyle;
	create_config << XOR(" ") << CFG.glowFriends << XOR(" ") << CFG.glowFriendColor[0] << XOR(" ") << CFG.glowFriendColor[1] << XOR(" ") << CFG.glowFriendColor[2] << XOR(" ") << CFG.glowFriendColor[3] << XOR(" ") << CFG.selectedGlowFriendStyle;
	create_config << XOR(" ") << CFG.clrRender << XOR(" ") << CFG.clrRenderColor[0] << XOR(" ") << CFG.clrRenderColor[1] << XOR(" ") << CFG.clrRenderColor[2] << XOR(" ") << CFG.clrRenderFriendColor[0] << XOR(" ") << CFG.clrRenderFriendColor[1] << XOR(" ") << CFG.clrRenderFriendColor[2];
	create_config << XOR(" ") << CFG.hitSound << XOR(" ") << CFG.selectedSound;
	create_config << XOR(" ") << CFG.bunnyHop;
	create_config << XOR(" ") << CFG.AimBotB << XOR(" ") << CFG.aimFov << XOR(" ") << CFG.aimSmooth << XOR(" ") << CFG.aimBone << XOR(" ") << CFG.aimVisibleCheck;
	create_config << XOR(" ") << CFG.triggerBot;
	create_config << XOR(" ") << CFG.models << XOR(" ") << CFG.selectedModels;
	create_config.close(); 
}

void configurationSystem::LoadConfig()
{
	std::ifstream load_config(XOR("config.ini")); 
	if (!load_config)
		SaveConfig();

	load_config >> CFG.radar;
	load_config >> CFG.glow >> CFG.glowColor[0] >> CFG.glowColor[1] >> CFG.glowColor[2] >> CFG.glowColor[3] >> CFG.selectedGlowStyle;
	load_config >> CFG.glowFriends >> CFG.glowFriendColor[0] >> CFG.glowFriendColor[1] >> CFG.glowFriendColor[2] >> CFG.glowFriendColor[3] >> CFG.selectedGlowFriendStyle;
	load_config >> CFG.clrRender >> CFG.clrRenderColor[0] >> CFG.clrRenderColor[1] >> CFG.clrRenderColor[2] >> CFG.clrRenderFriendColor[0] >> CFG.clrRenderFriendColor[1] >> CFG.clrRenderFriendColor[2];
	load_config >> CFG.hitSound >> CFG.selectedSound;
	load_config >> CFG.bunnyHop;
	load_config >> CFG.AimBotB >> CFG.aimFov >> CFG.aimSmooth >> CFG.aimBone >> CFG.aimVisibleCheck;
	load_config >> CFG.triggerBot;
	load_config >> CFG.models >> CFG.selectedModels;
	load_config.close(); 
}