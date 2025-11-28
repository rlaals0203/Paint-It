#include "pch.h"
#include "GuidedProjectile.h"
#include "PlayerFindManager.h"
#include "Object.h"

GuidedProjectile::GuidedProjectile() : Projectile()
{
}

GuidedProjectile::~GuidedProjectile()
{
}

void GuidedProjectile::Init(std::wstring _texture, float _damage)
{
	Projectile::Init(_texture, _damage);
	m_target = GET_SINGLE(PlayerFindManager)->GetPlayer();
}

void GuidedProjectile::Update()
{
	if (m_isStop) return;
	Vec2 dir = (m_target->GetPos() - GetPos());
	dir.Normalize();
	Translate({ dir.x * m_speed * fDT,  dir.y * m_speed * fDT });
}

void GuidedProjectile::Render(HDC _hdc)
{
	Projectile::Render(_hdc);
}

void GuidedProjectile::EnterCollision(Collider* _other)
{
	Projectile::EnterCollision(_other);
}