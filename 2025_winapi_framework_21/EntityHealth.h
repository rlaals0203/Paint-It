#pragma once
#include "Component.h"

class EntityHealth : Component
{
public:
	EntityHealth();
	~EntityHealth();
public:
	const int& GetCurrentHp() const { return m_currentHp; }
	const int& GetMaxHp() const { return m_maxHp; }
	void ApplyDamage(int _damage);
private:
	Object* m_owner;

	int m_maxHp;
	int m_currentHp;
};

