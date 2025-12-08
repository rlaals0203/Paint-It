#pragma once
#include "Object.h"
#include "Animator.h"
#include "EntityHealth.h"
#include "DOTweenCompo.h"
class TorchObject :
    public Object
{
public:
    TorchObject(int m_count, Vec2 _pos, float _offset = 0.f);
    ~TorchObject();
public:
    void Render(HDC _hdc) override;
    void Update() override;
private:
    void HandleDead();
    void FireProjectile();
private:
    DOTweenCompo* m_dotweenCompo;
    Animator* m_animator;
    std::wstring m_animName;
    Vec2 m_pos;
    float m_delay;
    float m_time;
    float m_count;
    float m_lifeTime = 10.f;

    bool m_isDead;
};

