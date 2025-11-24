#pragma once
#include"pch.h"
#include "Texture.h"

struct EffectData
{
	wstring animName;
	Texture* tex;
	Vec2 lt;
	Vec2 slice;
	Vec2 step;
	UINT frameCount;
	float frameDuration;
};