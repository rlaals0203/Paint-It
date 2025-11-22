#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "ProjectileManager.h"
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
	AddComponent<Rigidbody>();
	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(L"jiwooFront",m_pTexture,{0.f,150.f}
	,{50.f,50.f} ,{50.f,0.f} ,5,1.f);
	animator->Play(L"jiwooFront");
}

Player::~Player()
{
}

void Player::Render(HDC _hdc)
{
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

void Player::ExitCollision(Collider* _other)
{
	if (_other->GetName() == L"Floor")
	{
		Rigidbody* rb = GetComponent<Rigidbody>();
		rb->SetGrounded(false);
		m_isGrounded = false;
	}
}

void Player::Update()
{
	Object::Update();

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
	m_coolTime -= fDT;

	if (GET_KEY(KEY_TYPE::LBUTTON) && m_coolTime < 0.f)
	{
		Vec2 playerPos = GetPos();
		Vec2 shootDir = m_isRight ? Vec2{ 1.f, 0.f } : Vec2{ -1.f, 0.f };

		GET_SINGLE(ProjectileManager)->SpawnProjectile(ProjectileType::Player, 20.f, playerPos, shootDir);

		m_coolTime = m_stat.delay;
	}

	if (GET_KEYDOWN(KEY_TYPE::LSHIFT))
	{
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vec2 velo = rb->GetVelocity();
		int force = m_isRight ? 1 : -1;
		Vec2 dir = { (float)(force * 3500), velo.y };
		rb->SetVelocity(dir);
	}
}

void Player::Jump()
{
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->SetVelocity({ rb->GetVelocity().x, -550.f });
	rb->SetGrounded(false);
}