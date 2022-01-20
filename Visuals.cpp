#include "Visuals.h"

Visuals * iVisuals;
GlowStruct EGlow;
ClrRender clrChams;

GlowStruct Visuals::SetGlowColor(GlowStruct Glow, DWORD entity)
{
	switch (CFG.glowFriends)
	{
	case TRUE:
		if (LocalPlayer::getLocalTeam() != Entity::getEntityTeam(entity))
		{
			Glow.r = CFG.glowColor[0];
			Glow.g = CFG.glowColor[1];
			Glow.b = CFG.glowColor[2];
			Glow.a = CFG.glowColor[3];
			Glow.glowStyle = CFG.selectedGlowStyle;
		}
		else
		{
			Glow.r = CFG.glowFriendColor[0];
			Glow.g = CFG.glowFriendColor[1];
			Glow.b = CFG.glowFriendColor[2];
			Glow.a = CFG.glowFriendColor[3];
			Glow.glowStyle = CFG.selectedGlowFriendStyle;
		}
	case FALSE:
		if (LocalPlayer::getLocalTeam() != Entity::getEntityTeam(entity))
		{
			Glow.r = CFG.glowColor[0];
			Glow.g = CFG.glowColor[1];
			Glow.b = CFG.glowColor[2];
			Glow.a = CFG.glowColor[3];
			Glow.glowStyle = CFG.selectedGlowStyle;
		}
	}
	Glow.m_bRenderWhenOccluded = true; 
	Glow.m_bRenderWhenUnoccluded = false; 
	return Glow; 
}


void Visuals::Glow(DWORD entity)
{

	EGlow = mem->read<GlowStruct>(LocalPlayer::getGlowObjects() + (Entity::getGlowIndex(entity) * 0x38));
	EGlow = iVisuals->SetGlowColor(EGlow, entity);
	mem->write<GlowStruct>(LocalPlayer::getGlowObjects() + (Entity::getGlowIndex(entity) * 0x38), EGlow);
}

void Visuals::RenderChams(DWORD entity)
{
	if (LocalPlayer::getLocalTeam() != Entity::getEntityTeam(entity))
	{
		clrChams.red = CFG.clrRenderColor[0] * 255;
		clrChams.green = CFG.clrRenderColor[1] * 255;
		clrChams.blue = CFG.clrRenderColor[2] * 255;
	}
	else
	{
		clrChams.red = CFG.clrRenderFriendColor[0] * 255;
		clrChams.green = CFG.clrRenderFriendColor[1] * 255;
		clrChams.blue = CFG.clrRenderFriendColor[2] * 255;
	}
	mem->write<ClrRender>(entity + OFF.m_clrRender, clrChams);
}

int Visuals::InGameRadar(DWORD entity)
{

	if (LocalPlayer::getLocalBase() != Entity::getEntityTeam(entity))
		return mem->write<int>(entity + OFF.m_bSpotted, 1);
}