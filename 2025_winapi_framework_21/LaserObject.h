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
    void SetLine();
    void ShowDangerGizmo(Vec2 finalPos, Vec2 finalSize);
public:
    void SetWidth(float _width) { m_width = _width; }
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

