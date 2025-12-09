#pragma once
#include "SpriteObject.h"
#include "Collider.h"

class Platform :
    public SpriteObject
{
public:
    Platform(Vec2 _start, Vec2 _end);
    ~Platform();

    void Render(HDC _hdc) override;
private:
    Collider* m_collider;
};

