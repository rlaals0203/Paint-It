#pragma once
#include "Effect.h"
#include "EffectData.h"

enum class EffectType
{
	TestPlayer,
	SmashSmoke,
	FireExplosion,
	BlackHole,
	None
};


class EffectManager
{
    DECLARE_SINGLE(EffectManager);
public:
    void Init();

    ~EffectManager()
    {
        m_effects.clear();
    }

    void RegisterEffect(EffectType type, wstring animName, Texture* tex,
        Vec2 lt, Vec2 slice, Vec2 step, UINT frameCount, float duration);
    void PlayEffect(EffectType _type, Vec2 _pos, Vec2 _size,
        float _duration, bool _loop = false);

private:
    std::unordered_map<EffectType, EffectData> m_effects;
};

