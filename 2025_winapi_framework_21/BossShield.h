#pragma once
#include "Object.h"
#include "Texture.h"
#include "Animator.h"
class BossShield :
    public Object
{
public:
    BossShield();
    ~BossShield();
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
private:
    Animator* m_animator;
};

