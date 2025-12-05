#pragma once
#include "Object.h"

class Texture;
class Animator;

class BurstSkill : public Object
{
public:
    BurstSkill();
    ~BurstSkill();

public:
    void Init(Vec2 _playerPos, float _radius, float _duration);
    void Update() override;
    void Render(HDC _hdc) override;

private:
    void DestroyProjectilesInRange();

private:
    Animator* m_animator;
    Texture* m_burstTexture;
    float m_radius;
    float m_duration;
    float m_timer;
    bool m_hasTriggered;
    std::wstring m_burstAnim;
};