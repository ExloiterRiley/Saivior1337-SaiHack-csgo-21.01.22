#pragma once
#include "m_headers.h"

class Math
{
public:
	void MakeVector(float* pfIn, float* pfOut);
	void Angles(float* src, float* dst, float* angles);
	D3DXVECTOR3 CalcAngle(register const D3DXVECTOR3& src, register const D3DXVECTOR3& dst, float* punch);
	float GetFOV(float* angle, float* src, float* dst);
	D3DXVECTOR3 ClampAngle(D3DXVECTOR3 qaAng);
};

extern Math * iMath;
