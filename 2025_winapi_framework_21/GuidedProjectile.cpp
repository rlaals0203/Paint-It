#include "pch.h"
#include "GuidedProjectile.h"
#include "PlayerFindManager.h"
#include "Object.h"
#include "SceneManager.h"

GuidedProjectile::GuidedProjectile() : Projectile(), m_isStop(false)
{
}

GuidedProjectile::~GuidedProjectile()
{
}

void GuidedProjectile::Init(std::wstring _texture, float _speed, float _damage, float _lifeTime)
{
	Projectile::Init(_texture, _damage);
	m_speed = _speed;
	m_damage = _damage;
	m_lifeTime = _lifeTime;
	m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::ENEMYOBSTACLE);
}

void GuidedProjectile::Update()
{
	if (m_isStop) return;
	Vec2 dir = (m_player->GetPos() - GetPos());
	dir.Normalize();
	Translate({ dir.x * m_speed * fDT,  dir.y * m_speed * fDT });

	m_lifeTime -= fDT;
	if (m_lifeTime < 0.f)
	{
		GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
	}
}

void GuidedProjectile::Render(HDC _hdc)
{
	Projectile::Render(_hdc);
	ComponentRender(_hdc);
}

void GuidedProjectile::EnterCollision(Collider* _other)
{
	Projectile::EnterCollision(_other);
}

void GuidedProjectile::HandleDead()
{
}
