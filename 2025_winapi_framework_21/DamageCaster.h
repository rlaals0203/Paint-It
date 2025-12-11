#pragma once
#include "Object.h"
class DamageCaster :
    public Object
{
public:
    DamageCaster();
    ~DamageCaster();

    void StayCollision(Collider* _collide) override;
    void Update() override;
public:
    void CastDamage(Vec2 _pos, Vec2 _size, int _damage);
private:
    bool m_isCastFrame = false;
    bool m_deleteNextFrame = false;
    int m_damage;
};

