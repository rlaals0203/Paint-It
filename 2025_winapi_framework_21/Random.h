#pragma once
#include "pch.h"

class Random
{
public:
	static float Range(float _min, float _max)
	{
		float t = (float)rand() / (float)RAND_MAX;
		return _min + t * (_max - _min);
	}
};