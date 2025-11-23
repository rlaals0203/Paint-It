#include "pch.h"
#include "EntityHealth.h"
#include "Object.h"

EntityHealth::EntityHealth() : 
	m_maxHp(0), 
	m_currentHp(0) { }

EntityHealth::~EntityHealth() { }

void EntityHealth::Init()
{
}

void EntityHealth::LateUpdate()
{
	Object* owner = GetOwner();
}

void EntityHealth::Render(HDC _hdc)
{
}

void EntityHealth::ApplyDamage(int _damage)
{
	cout << "SDf";
	m_currentHp -= _damage;
	Object* owner = GetOwner();
	owner->OnHit();

	if (m_currentHp <= 0.f)
	{
		owner->SetDead();
	}
}
