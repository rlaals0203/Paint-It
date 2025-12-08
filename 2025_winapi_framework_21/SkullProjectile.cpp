#include "pch.h"
#include "SkullProjectile.h"
#include "ResourceManager.h"

SkullProjectile::SkullProjectile()
{
	m_skullName = L"skullprojectile";
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(L"skullprojectile");

	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetDefaultHP(100.f);
	m_lifeTime = 8.f;
}

SkullProjectile::~SkullProjectile()
{
}

void SkullProjectile::Init(std::wstring _texture, float _speed, float _damage, float _lifeTime)
{
	GuidedProjectile::Init(_texture, _speed, _damage, _lifeTime);
}

void SkullProjectile::Update()
{
	m_isRight = m_player->GetPos().x > GetPos().x;

	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.f)
		Explosion();

	GuidedProjectile::Update();
}

void SkullProjectile::Render(HDC _hdc)
{
	GuidedProjectile::Render(_hdc);
}

void SkullProjectile::EnterCollision(Collider* _other)
{
	GuidedProjectile::EnterCollision(_other);
}

void SkullProjectile::Explosion()
{
}
