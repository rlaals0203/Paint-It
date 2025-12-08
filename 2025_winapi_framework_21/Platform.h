#pragma once
#include "SpriteObject.h"
#include "Player.h"
#include "Collider.h"

class Platform :
    public SpriteObject
{
public:
    Platform(Vec2 _start, Vec2 _end);
    ~Platform();

    void Render(HDC _hdc) override;
    void Update() override;
private:
    Player* m_player;
    Collider* m_collider;
};

