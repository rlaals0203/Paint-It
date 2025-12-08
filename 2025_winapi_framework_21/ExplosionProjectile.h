#pragma once
#include "Projectile.h"
class ExplosionProjectile :
    public Projectile
{
public:
    ExplosionProjectile();
    ~ExplosionProjectile();

    void Update() override;
    void Render(HDC _hdc) override;
    void Init(std::wstring _texture, float _damage) override;
    void EnterCollision(Collider* _other) override;
private:
    bool m_isExplosed;
    float m_explosionTime = 1.f;
};

