#pragma once
#include "GuidedProjectile.h"
#include "EntityHealth.h"
#include "Animator.h"
#include "Player.h"

class SkullProjectile :
    public Projectile
{
public:
    SkullProjectile();
    ~SkullProjectile();
public:
    void Init(float _speed, float _damage, float _lifeTime);
    void Update() override;
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
private:
    void Explosion();
private:
    Player* m_player;
    Animator* m_animator;
    Texture* m_texture;
    EntityHealth* m_healthCompo;
    std::wstring m_skullName;
    std::wstring m_rskullName;
    std::wstring m_bskullName;
    std::wstring m_rbskullName;
    bool m_isRight;
    float m_lifeTime;
};

