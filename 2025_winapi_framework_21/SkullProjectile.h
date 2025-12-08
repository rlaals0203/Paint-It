#pragma once
#include "GuidedProjectile.h"
#include "EntityHealth.h"

class SkullProjectile :
    public GuidedProjectile
{
public:
    SkullProjectile();
    ~SkullProjectile();
public:
    void Init(std::wstring _texture, float _speed, float _damage, float _lifeTime);
    void Update() override;
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
private:
    void Explosion();
private:
    Animator* m_animator;
    Texture* m_texture;
    EntityHealth* m_healthCompo;
    std::wstring m_skullName;
    bool m_isRight;
    float m_lifeTime;
};

