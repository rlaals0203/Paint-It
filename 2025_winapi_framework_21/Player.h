#pragma once
#include "Object.h"
#include "ProjectileLauncher.h"
#include "Animator.h"
#include "EntityHealth.h"
class Texture;

struct PlayerStat
{

};

class Player : public Object
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	void Jump();
	void UseBurstSkill();
	virtual void EnterCollision(Collider* _other)override;
	virtual void ExitCollision(Collider* _other)override;
	void SetSpeed(float _speed) { m_speed = _speed; }
	void SetOiledTime(float _time) {
		m_oiledTime = _time;
		m_isOiled = true;
		m_speed = 1.f;
	}

	void SetAnimationParam();
	void FireProjectile();
	void PlayerMovement();
	void Dash();
	void Move();

	void SetCompletedFire() { m_completedFire = true; }
	void SetCompletedPrism() { m_completedPrism = true; }
private:
	Texture* m_pTexture;
	Texture* m_rpTexture;
	Texture* m_blinkTexture;
	Texture* m_rblinkTexture;

	Animator* m_animator;
	PlayerStat m_stat;
	EntityHealth* m_healthCompo;
private:
	bool m_isDie;
	bool m_isGrounded;
	bool m_isOiled;
	bool m_completedFire;
	bool m_completedPrism;

	float m_coolTime;
	float m_isMoving;
	float m_speed = 3.f;
	float m_delay = 0.5f;
	float m_oiledTime;

	float m_burstCoolTime = 3.f;
	float m_burstCooldown = 0.f;

	float m_dashCoolTime = 0.25f;
	float m_currentDashTime;

	std::wstring m_playerIdle;
	std::wstring m_rplayerIdle;
	std::wstring m_playerMove;
	std::wstring m_rplayerMove;
	std::wstring m_playerJump;
	std::wstring m_rPlayerJump;

	std::wstring m_bplayer;
	std::wstring m_brplayer;
};