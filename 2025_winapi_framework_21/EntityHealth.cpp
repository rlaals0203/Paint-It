#include "pch.h"
#include "EntityHealth.h"
#include "Object.h"

EntityHealth::EntityHealth() : 
	m_owner(nullptr), 
	m_maxHp(0), 
	m_currentHp(0) { }

EntityHealth::~EntityHealth() { }

void EntityHealth::ApplyDamage(int _damage)
{
	m_currentHp -= _damage;
	m_owner->OnHit();

	if (m_currentHp <= 0.f)
	{
		m_owner->SetDead();
	}
}
