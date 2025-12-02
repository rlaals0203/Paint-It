#pragma once
#include "SpriteObject.h"
#include "EntityHealth.h"
#include "PrismBoss.h"
#include "Animator.h"

class PrismObject :
    public Object
{
public:
    PrismObject(Vec2 _pos, PrismBoss* _boss);
    ~PrismObject();
public:
    void Update() override;
    void Render(HDC _hdc) override;
private:
    EntityHealth* m_healthCompo;
    Animator* m_animator;
    PrismBoss* m_boss;
};

