#pragma once
#include "Object.h"
#include "ProjectileLauncher.h"
class Texture;

struct PlayerStat //플레이어 스탯 저장 구조체
{
	float speed = 2.5f;
	float delay = 0.f;
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
	PlayerStat m_stat;
private:
	bool m_isRight; //오른쪽을 보고 있는지
	bool m_isDie;
	bool m_isGrounded;
	float m_coolTime;
};

