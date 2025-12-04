#pragma once
#include "Object.h"
#include "DOTweenCompo.h"
#include "Collider.h"

class LaserObject :
    public Object
{
public:
    LaserObject();
    ~LaserObject();

    void Update() override;
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
public:
    void InitLaser(Vec2 _start, float _angle, float _duration, float _delay = 1.f);
    void HideLine();
    void HideLineWithAnim();
    void SetLine();
    void ShowDangerGizmo(Vec2 finalPos, Vec2 finalSize);
    void SetWidth(float _width) { m_width = _width; }
    Vec2 GetLaserHitPoint();
    Vec2 GetDirection() { return m_dir; }

private:
    DOTweenCompo* m_dotweenCompo;
    Collider* m_collider;
    Vec2 m_pos;
    Vec2 m_dir;
    bool m_isDelay;
    float m_delay;
    float m_duration;
    float m_angle;
    float m_length;
    float m_width;
};

