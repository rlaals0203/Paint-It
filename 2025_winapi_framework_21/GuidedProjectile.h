#pragma once
#include "Projectile.h"
#include "Player.h"
class GuidedProjectile :
    public Projectile
{
public:
    GuidedProjectile();
    ~GuidedProjectile();

    void Init(std::wstring _texture, float _speed, float _damage, float _lifeTime);
    void Update() override;
    void Render(HDC _hdc) override;

    void EnterCollision(Collider* _other) override;
public:
    void SetStop() { m_isStop = true; }
    void SetPlay() { m_isStop = false; }
private:
    Player* m_target;
    bool m_isStop;
};

