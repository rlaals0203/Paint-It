#include "pch.h"
#include "ExplosionProjectile.h"
#include "EffectManager.h"

ExplosionProjectile::ExplosionProjectile()
{
}

ExplosionProjectile::~ExplosionProjectile()
{
}

void ExplosionProjectile::Update()
{
	if (m_isExplosed) {
		m_explosionTime -= fDT;
		if (m_explosionTime <= 0.f)
			SetDead();
	}
}

void ExplosionProjectile::Render(HDC _hdc)
{
}

void ExplosionProjectile::Init(std::wstring _texture, float _damage)
{
	Projectile::Init(_texture, _damage);
}

void ExplosionProjectile::EnterCollision(Collider* _other)
{
	Projectile::EnterCollision(_other);
	GET_SINGLE(ResourceManager)->Play(L"explosion");
	GET_SINGLE(EffectManager)->PlayEffect(EffectType::FireExplosion, 
		GetPos(), { 3, 3 }, m_explosionTime);

	m_isExplosed = true;
}
