#pragma once
#include "SpriteObject.h"
class HealPack :
    public SpriteObject
{
public:
    HealPack(std::wstring _texture, Layer _layer);
    ~HealPack();

    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
private:
    int m_healAmount;
};

