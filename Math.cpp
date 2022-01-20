#include "Math.h"
#define M_RADPI 57.295779513082f

Math * iMath;

void Math::MakeVector(float* pfIn, float* pfOut)
{
	float pitch; 
	float yaw; 
	float tmp; 

	pitch = (float)(pfIn[0] * M_PI / 180); 
	yaw = (float)(pfIn[1] * M_PI / 180); 
	tmp = (float)cos(pitch); 

	pfOut[0] = (float)(-tmp * -cos(yaw)); 
	pfOut[1] = (float)(sin(yaw) * tmp); 
	pfOut[2] = (float)-sin(pitch); 
}


void Math::Angles(float* src, float* dst, float* angles)
{
	double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) }; 
	double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]); 

	angles[0] = (float)(atan(delta[2] / hyp) * M_RADPI); 
	angles[1] = (float)(atan(delta[1] / delta[0]) * M_RADPI); 
	angles[2] = 0.0f; 

	if (delta[0] >= 0.0) { angles[1] += 180.0f;  }
}

D3DXVECTOR3 Math::CalcAngle(register const D3DXVECTOR3& src, register const D3DXVECTOR3& dst, float* punch)
{
	D3DXVECTOR3 angles; 
	D3DXVECTOR3 delta = src - dst; 
	float hyp = sqrt(delta.x * delta.x + delta.y * delta.y); 
	angles.x = atan(delta.z / hyp) * (180.0f / M_PI) - (punch[0] * 2.0f);  //asinf
	angles.y = atanf(delta.y / delta.x) * (180.0f / M_PI) - (punch[1] * 2.0f) + !((*(DWORD*)&delta.x) >> 31 & 1) * 180.0f; 
	angles.z = 0.0f; 
	return angles;
}


float Math::GetFOV(float* angle, float* src, float* dst)
{
	float ang[3], aim[3]; 
	float fov; 

	Angles(src, dst, ang); 
	MakeVector(angle, aim); 
	MakeVector(ang, ang); 

	float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2])); 
	float mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2])); 

	float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2]; 

	fov = acos(u_dot_v / (mag_s * mag_d)) * (180.0f / M_PI); 

	return fov;
}


D3DXVECTOR3 Math::ClampAngle(D3DXVECTOR3 qaAng)
{
	if (qaAng.x > 89.0f)
		qaAng.x = 89.0f; 
	if (qaAng.x < -89.0f)
		qaAng.x = -89.0f; 
	while (qaAng.y > 180.0f)
		qaAng.y -= 360.0f; 
	while (qaAng.y < -180.0f)
		qaAng.y += 360.0f; 
	qaAng.z = 0; 
	return qaAng; 
}