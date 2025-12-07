#pragma once
#include "Projectile.h"
#include "Player.h"
class GuidedProjectile :
    public Projectile
{
public:
    GuidedProjectile();
    ~GuidedProjectile();
public:
    void Init(std::wstring _texture, float _speed, float _damage, float _lifeTime);
    void Update() override;
    void Render(HDC _hdc) override;

    void EnterCollision(Collider* _other) override;
public:
    void SetStop() { m_isStop = true; }
    void SetPlay() { m_isStop = false; }
private:
    void HandleDead();
protected:
    Player* m_player;
private:
    bool m_isStop;
};

