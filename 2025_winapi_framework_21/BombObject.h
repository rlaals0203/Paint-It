#pragma once
#include "Object.h"
class Texture;
class BombObject :
    public Object
{
public:
    BombObject(int damage , float endtime, Texture* tex);
    ~BombObject();
public:
    virtual void Render(HDC _hdc) override;
    virtual void Update() override;
    virtual void EnterCollision(Collider* _other) override;

public:
    void SetDamage(int damage) { m_damage = damage; }

private:
    int m_damage;

    float m_damageTime;

    Texture* m_bombTex = nullptr;
};

