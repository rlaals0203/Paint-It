#include "pch.h"
#include "Effect.h"
#include "EffectManager.h"

Effect::Effect() : m_animator(nullptr), m_duration(0.f), m_isPlaying(false)
{

}

Effect::~Effect()
{ 

}

void Effect::Update()
{
	if (m_isPlaying == false) return;

	m_duration -= fDT;
	if (m_duration < 0.f)
	{
        m_isPlaying = false;
		SetDead();
	}
}

void Effect::Render(HDC _hdc)
{
    ComponentRender(_hdc);
}

void Effect::Init(const EffectData& _data, float _duration, bool _loop)
{
    if (m_animator == nullptr)
        m_animator = AddComponent<Animator>();

    m_duration = _duration;
    m_isPlaying = true;
    Play(_data, _loop);
}

void Effect::Play(const EffectData& _data, bool _loop)
{
    if (m_animator->FindAnimation(_data.animName) == nullptr)
    {
        m_animator->CreateAnimation(
            _data.animName,
            _data.tex,
            _data.lt,
            _data.slice,
            _data.step,
            _data.frameCount,
            _data.frameDuration);
    }

    PlayMode mode = _loop ? PlayMode::Loop : PlayMode::Once;
    m_animator->Play(_data.animName, mode);
    m_isPlaying = true;
}