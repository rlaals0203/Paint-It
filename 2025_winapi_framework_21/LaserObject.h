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

    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
public:
    void ShowLine(Vec2 _start, float _angle, float _duration);
    void HideLine();
    void SetLine();
    void ShowDangerGizmo(Vec2 finalPos, Vec2 finalSize);
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
};

