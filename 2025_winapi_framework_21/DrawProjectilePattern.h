#pragma once
#include "BossPattern.h"
#include "GuidedProjectile.h"
#include "SpriteObject.h"
#include "Player.h"
#include <stack>

class DrawProjectilePattern :
    public BossPattern
{
public:
    DrawProjectilePattern(BossController* _controller, std::wstring _texture, std::wstring _sprite, float _delay, float _damage);
    ~DrawProjectilePattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    std::stack<Projectile*> m_projectiles;
    std::wstring m_texture;
    std::wstring m_sprite;
    Player* m_player;
    SpriteObject* m_brushObj;
    float m_delay;
    float m_projTime;
    float m_time;
    float m_fireTime;
    float m_damage;
    bool m_isFireTime;
};

