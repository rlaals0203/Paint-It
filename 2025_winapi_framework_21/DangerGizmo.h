#pragma once
#include "Object.h"
#include "Texture.h"
class DangerGizmo :
    public Object
{
public:
    DangerGizmo();
    ~DangerGizmo();

    void Update() override;
    void Render(HDC _hdc) override;
public:
    void SetDangerGizmo(Vec2 _pos, Vec2 _size, float _angle, float _duration, float delay = 0.f);
private:
    Texture* m_texture1;
    Texture* m_texture2;

    float m_lifeTime;
    float m_colorTime;
    float m_delay;
    float m_angle;
    Vec2 m_size;
    Vec2 m_pos;
    bool m_isPlaying;
    bool m_isDelay;
    bool m_isRed;
};

