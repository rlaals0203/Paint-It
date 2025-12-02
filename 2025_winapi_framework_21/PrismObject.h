#pragma once
#include "SpriteObject.h"
#include "EntityHealth.h"
#include "PrismBoss.h"

class PrismObject :
    public SpriteObject
{
public:
    PrismObject(Vec2 _pos, std::wstring _texture,
        Layer _layer, PrismBoss* _boss);
    ~PrismObject();
public:
    void Update() override;
    void Render(HDC _hdc) override;
private:
    EntityHealth* m_healthCompo;
    PrismBoss* m_boss;
};

