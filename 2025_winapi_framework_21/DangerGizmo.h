#pragma once
#include "Object.h"
class DangerGizmo :
    public Object
{
public:
    DangerGizmo();
    ~DangerGizmo();

    void Update() override;
    void Render(HDC _hdc) override;
public:
    void SetDangerGizmo(Vec2 _pos, Vec2 _size, float _duration);
private:
    float m_lifeTime;
    Vec2 m_size;
    Vec2 m_pos;
    bool m_isPlaying;
};

