#pragma once
#include "Component.h"

class EntityHealth : 
	public Component
{
public:
	EntityHealth();
	~EntityHealth();
	void Init() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
public:
	const int& GetCurrentHp() const { return m_currentHp; }
	const int& GetMaxHp() const { return m_maxHp; }
	void ApplyDamage(int _damage);
	void SetDefaultHP(int _hp) { m_maxHp = m_currentHp = _hp; }
private:
	int m_maxHp;
	int m_currentHp;
};

