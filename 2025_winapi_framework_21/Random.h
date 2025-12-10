#pragma once
#include "pch.h"

class Random
{
public:
	static float Range(float _min, float _max)
	{
		float n = (float)rand() / (float)RAND_MAX;
		return _min + n * (_max - _min);
	}
};