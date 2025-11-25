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
	com->SetSize({ 20, 20 });
	com->SetName(L"Proj");
	com->SetTrigger(true);
}

void Projectile::Update()
{
	float speed = m_speed * 100;
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
	_other->GetOwner()->GetComponent<EntityHealth>()->ApplyDamage(m_damage);
	DamageText* dmgText = new DamageText();
	dmgText->Init((int)m_damage, GetPos());
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(dmgText, Layer::EFFECT);
	//GET_SINGLE(EffectManager)->PlayEffect(EffectType::Player, GetPos(), 1.f, false);
	SetDead();
}

void Projectile::ExitCollision(Collider* _other)
{
}
