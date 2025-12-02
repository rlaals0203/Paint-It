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
	void SetIsPlayer(bool _isBoss = true) { m_isBoss = _isBoss; }
	void SubscribeOnDead(std::function<void()> _callback) { m_callback = _callback; }
private:
	int m_maxHp;
	int m_currentHp;
	bool m_isBoss;
	std::function<void()> m_callback;
};

