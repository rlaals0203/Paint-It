#pragma once
class PlayerStat
{
public:
	float GetSpeed() { return m_speed; }
	float GetCooltime() { return m_coolTime; }
	float GetJumpForce() { return m_jumpForce; }
private:
	float m_speed = 3.f;
	float m_coolTime = 1.f;
	float m_jumpForce = 5.f;
};

