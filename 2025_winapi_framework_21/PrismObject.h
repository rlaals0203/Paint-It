#pragma once
#include "SpriteObject.h"
#include "EntityHealth.h"
#include "PrismBoss.h"
#include "Animator.h"

class PrismObject :
    public SpriteObject
{
public:
    PrismObject(Vec2 _pos, PrismBoss* _boss);
    ~PrismObject();
public:
    void Render(HDC _hdc) override;
    void OnDead();
private:
    EntityHealth* m_healthCompo;
    PrismBoss* m_boss;
};

