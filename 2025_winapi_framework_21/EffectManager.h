#pragma once
#include "Effect.h"
#include "EffectData.h"

enum class EffectType
{
	Player,
	Enemy,
	None
};


class EffectManager
{
	DECLARE_SINGLE(EffectManager);
public:
	void Init();
public:
	void RegisterEffect(EffectType type, wstring animName,
		Texture* tex, Vec2 lt, Vec2 slice, Vec2 step, 
		UINT frameCount, float frameDuration);

	void PlayEffect(EffectType _type, Vec2 _pos, 
		float duration, bool _loop);
private:
	std::unordered_map<EffectType, EffectData> m_effects;
};

