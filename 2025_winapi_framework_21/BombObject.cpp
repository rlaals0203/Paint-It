#include "pch.h"
#include "BombObject.h"
#include "Collider.h"
#include "EntityHealth.h"
#include "DamageText.h"
#include "Texture.h"

BombObject::BombObject(int damage, float endtime)
	: m_damage(damage)
	, m_damageTime(endtime)
{
}

BombObject::~BombObject()
{
}

void BombObject::Render(HDC _hdc)
{
	LONG width = m_bombTex->GetWidth();
	LONG height = m_bombTex->GetHeight();

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	::TransparentBlt(_hdc
		, pos.x
		, pos.y
		, size.x
		, size.y
		, m_bombTex->GetTextureDC(),
		0, 0, width, height, RGB(255, 0, 255));
}

void BombObject::Update()
{
	m_damageTime -= fDT;
	if (m_damageTime < 0)
	{
		SetDead();
	}
}

void BombObject::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Player")
	{
		auto* healthCompo = _other->GetOwner()->GetComponent<EntityHealth>();
		if (healthCompo)
		{
			healthCompo->ApplyDamage(m_damage, true);
		}
	}
}
