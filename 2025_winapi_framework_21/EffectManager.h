#pragma once
#include "Effect.h"

enum EffectType
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
	void RegisterEffect(EffectType _type, wstring _texture);
	void PlayEffect(EffectType _type, float _duration, bool _isLoop = false);
private:
	std::unordered_map<EffectType, Effect*> m_effects;
};

