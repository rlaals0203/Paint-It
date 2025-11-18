#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
Player::Player()
	: m_pTexture(nullptr)
{
	m_pTexture = GET_SINGLE(ResourceManager)->GetTexture(L"jiwoo");
	AddComponent<Collider>();
	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(L"jiwooFront",m_pTexture,{0.f,150.f}
	,{50.f,50.f} ,{50.f,0.f} ,5,1.f);
	animator->Play(L"jiwooFront");
	AddComponent<Rigidbody>();
}

Player::~Player()
{
	//SAFE_DELETE(m_pTexture);
}

void Player::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	int width = m_pTexture->GetWidth();
	int height = m_pTexture->GetHeight();
	ComponentRender(_hdc);
}

void Player::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Floor")
	{
		Rigidbody* rb = GetComponent<Rigidbody>();
		m_isGrounded = true;
		rb->SetGrounded(true);
	}
}

void Player::Update()
{
	Vec2 dir = {};

	if (GET_KEY(KEY_TYPE::D))
	{
		m_isRight = true;
		dir.x += m_stat.speed;
	}
	else if (GET_KEY(KEY_TYPE::A))
	{
		m_isRight = false;
		dir.x -= m_stat.speed;
	}

	if (GET_KEY(KEY_TYPE::SPACE) && m_isGrounded) //점프 시도
	{
		Jump();
	}

	Translate({dir.x * 100.f * fDT, dir.y * 100.f * fDT});
}

void Player::Jump()
{
	m_isGrounded = false;
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->SetVelocity({ rb->GetVelocity().x, -550.f });
	rb->SetGrounded(false);
}

void Player::CreateProjectile()
{
	Projectile* proj = new Projectile;
	// set
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	proj->SetPos(pos);
	proj->SetSize({ 20.f,20.f });
	static float angle = 0.f;
	proj->SetAngle(angle * PI / 180);
	angle += 10.f;
	proj->SetDir({ 0.f,-1.f });
	GET_SINGLE(SceneManager)->GetCurScene()
		->AddObject(proj, Layer::PROJECTILE);
}
