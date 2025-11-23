#include "pch.h"
#include "Projectile.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "EntityHealth.h"
#include "Collider.h"

Projectile::Projectile() : m_angle(0.f) {}

Projectile::~Projectile()
{
}

void Projectile::Init(wstring _texture, float _speed, float _damage)
{
	m_textureName = _texture;
	m_pTexture = GET_SINGLE(ResourceManager)->GetTexture(_texture);
	m_speed = _speed;
	m_damage = _damage;

	auto* com = AddComponent<Collider>();
	com->SetSize({ 20.f,20.f });
	com->SetName(L"Proj");
	com->SetTrigger(true);
}

void Projectile::Update()
{
	Object::Update();
	if (m_isAngle)
		Translate({ cosf(m_angle) * 500.f * fDT,  sinf(m_angle) * 500.f * fDT });
	else
		Translate({ m_dir.x * 500.f * fDT,  m_dir.y * 500.f * fDT });
}

void Projectile::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	int width = m_pTexture->GetWidth();
	int height = m_pTexture->GetHeight();

		::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x, size.y,
		m_pTexture->GetTextureDC(),
		0, 0, width, height, RGB(255,0,255));
		ComponentRender(_hdc);
}

void Projectile::EnterCollision(Collider* _other)
{
	_other->GetOwner()->GetComponent<EntityHealth>()->ApplyDamage(m_damage);
	m_isDie = true;
}

void Projectile::ExitCollision(Collider* _other)
{

}
