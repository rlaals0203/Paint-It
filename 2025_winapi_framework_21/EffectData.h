#pragma once
#include "Texture.h"
#include "pch.h"

struct EffectData
{
    std::wstring animName;
    Texture* tex;
    Vec2 lt;
    Vec2 slice;
    Vec2 step;
    UINT frameCount;
    float frameDuration;
};
