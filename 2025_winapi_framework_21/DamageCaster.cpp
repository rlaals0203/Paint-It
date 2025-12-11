#include "pch.h"
#include "DamageCaster.h"
#include "Collider.h"
#include "EntityHealth.h"
#include "SceneManager.h"

DamageCaster::DamageCaster() : m_time(0.1f)
{
}

DamageCaster::~DamageCaster()
{
}

void DamageCaster::StayCollision(Collider* _collide)
{
    if (!m_isCastFrame) return;

    if (_collide->GetName() == L"Player") {
        auto* health = _collide->GetOwner()->GetComponent<EntityHealth>();
        health->ApplyDamage(m_damage);

        m_isCastFrame = false;
        m_deleteNextFrame = false;

        SetDead();
    }
}

void DamageCaster::Update()
{
    m_time -= fDT;
    if (m_time <= 0.f)
    {
        SetDead();  
        m_deleteNextFrame = false;
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
