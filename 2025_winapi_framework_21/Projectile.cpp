#include "pch.h"
#include "Projectile.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "EntityHealth.h"
#include "Collider.h"
#include "DamageText.h"
#include "EffectManager.h"

Projectile::Projectile() : m_angle(0.f) {}

Projectile::~Projectile() { }

void Projectile::Init(std::wstring _texture, float _damage)
{
	m_textureName = _texture;
	m_pTexture = GET_SINGLE(ResourceManager)->GetTexture(_texture);
	m_damage = _damage;

	auto* com = AddComponent<Collider>();
	com->SetName(L"Proj");
	com->SetTrigger(true);
}

void Projectile::Update()
{
	float speed = m_speed;
	Object::Update();
	if (m_isAngle)
	{
		float rad = m_angle * (3.1415926f / 180.f);
		Translate({ cosf(rad) * speed * fDT, sinf(rad) * speed * fDT });
	}
	else
		Translate({ m_dir.x * speed * fDT,  m_dir.y * speed * fDT });
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
		0, 0, width, height, RGB(255, 0, 255));
	ComponentRender(_hdc);
}

void Projectile::EnterCollision(Collider* _other)
{
	auto* healthCompo = _other->GetOwner()->GetComponent<EntityHealth>();
	DamageText* dmgText = new DamageText();
	dmgText->Init(std::to_wstring((int)m_damage), GetPos());

	if (healthCompo)
	{
		healthCompo->ApplyDamage(m_damage, false);
	}

	SetDead();
}