#include "pch.h"
#include "DamageCaster.h"
#include "Collider.h"
#include "EntityHealth.h"
#include "SceneManager.h"

DamageCaster::DamageCaster()
{
}

DamageCaster::~DamageCaster()
{
}

void DamageCaster::StayCollision(Collider* _collide)
{
	if (!m_deleteNextFrame) return;
	if (_collide->GetName() == L"Player") {
		auto* health = _collide->GetOwner()->GetComponent<EntityHealth>();
		health->ApplyDamage(m_damage);
	}
}

void DamageCaster::Update()
{
	if (m_deleteNextFrame)
	{
		SetDead();
		GET_SINGLE(SceneManager)->RequestDestroy(this);
		m_isCastFrame = false;
	}

	if (m_isCastFrame) {
		m_deleteNextFrame = true;
	}
}

void DamageCaster::CastDamage(Vec2 _pos, Vec2 _size, int _damage)
{
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::BACKDAMAGEABLE);
	m_damage = _damage;
	SetPos(_pos);
	auto* collider = AddComponent<Collider>();
	collider->SetSize(_size);
	m_isCastFrame = true;
	m_deleteNextFrame = true;
}
