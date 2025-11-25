#pragma once
#include "Object.h"
#include "Animator.h"
#include "EffectManager.h"
#include "EffectData.h"

class EffectManager;

class Effect :
    public Object
{
public:
    Effect();
    ~Effect();
    void Update() override;
    void Render(HDC _hdc) override;
public:
    void Init(const EffectData& _data, float _duration, bool _loop);
    void Play(const EffectData& _data, bool _loop);
private:
    Animator* m_animator;
    float m_duration;
    bool m_isPlaying;
};

