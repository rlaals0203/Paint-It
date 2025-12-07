#pragma once
#include "Object.h"
#include "Animator.h"
class TorchObject :
    public Object
{
public:
    TorchObject(int m_count, Vec2 _pos, float _offset = 0.f);
    ~TorchObject();
private:
    void HandleDead();
    void FireProjectile();
private:
    Animator* m_animator;
    std::wstring m_animName;
    Vec2 m_pos;
    float m_delay;
    float m_time;
    float m_count;
};

