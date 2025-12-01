#pragma once
#include "Object.h"
#include "ProjectileLauncher.h"
#include "Animator.h"
#include "EntityHealth.h"
class Texture;

struct PlayerStat //플레이어 스탯 저장 구조체
{
	float speed = 2.5f;
	float delay = 0.5f;
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
	virtual void EnterCollision(Collider* _other)override;
	virtual void ExitCollision(Collider* _other)override;
private:
	Texture* m_pTexture;
	Texture* m_rpTexture;
	Texture* m_blinkTexture;
	Animator* m_animator;
	PlayerStat m_stat;
	EntityHealth* m_healthCompo;
private:
	bool m_isDie;
	bool m_isGrounded;
	float m_coolTime;
	float m_isMoving;

	std::wstring m_playerIdle;
	std::wstring m_rplayerIdle;
	std::wstring m_bplayerIdle;
	std::wstring m_playerMove;
	std::wstring m_rplayerMove;
	std::wstring m_bplayerMove;
	std::wstring m_playerJump;
	std::wstring m_rPlayerJump;
	std::wstring m_bplayerJump;
};

