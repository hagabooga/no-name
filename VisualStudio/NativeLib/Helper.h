#pragma once
#include "Common.h"
class Helper
{
public:
	static float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	static float deg2rad(float deg)
	{
		return deg * Math_PI / 180;
	}
};