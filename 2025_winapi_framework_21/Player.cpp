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
#include "EntityHealth.h"
#include "PlayerFindManager.h"

Player::Player()
	: m_pTexture(nullptr)
{
	m_pTexture = GET_SINGLE(ResourceManager)->GetTexture(L"player");
	AddComponent<Collider>();
	AddComponent<Rigidbody>();
	auto* healthCompo = AddComponent<EntityHealth>();
	healthCompo->SetDefaultHP(100.f);
	m_animator = AddComponent<Animator>();

	m_animator->CreateAnimation
	(L"playerIdle", m_pTexture,
		{0.f,0.f}, {64.f, 64.f} ,
		{64.f,0.f}, 8, 0.1f);

	m_animator->CreateAnimation
	(L"playerMove", m_pTexture,
		{ 0.f, 64.f }, { 64.f, 64.f },
		{ 64.f,0.f }, 8, 0.1f);

	m_animator->CreateAnimation
	(L"playerJump", m_pTexture,
		{ 0.f, 128.f }, { 64.f, 64.f },
		{ 64.f,0.f }, 8, 0.1f);
	m_animator->Play(L"playerIdle");
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
	Rigidbody* rb = GetComponent<Rigidbody>();
	Vec2 velo = rb->GetVelocity();
	wstring animParam;
	m_isMoving = false;

	if (GET_KEY(KEY_TYPE::D))
	{
		m_isRight = true;
		m_isMoving = true;
		dir.x += m_stat.speed;
	}
	else if (GET_KEY(KEY_TYPE::A))
	{
		m_isRight = false;
		m_isMoving = true;
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
		Vec2 mousePos = GET_MOUSEPOS;
		Vec2 dir = mousePos - playerPos;
		dir.Normalize();

		GET_SINGLE(ProjectileManager)->SpawnProjectile(ProjectileType::PlayerProjectile, 20.f, playerPos, dir, true);
		m_coolTime = m_stat.delay;
	}

	if (GET_KEYDOWN(KEY_TYPE::LSHIFT))
	{
		int force = m_isRight ? 1 : -1;
		Vec2 dir = { (float)(force * 3500), velo.y };
		rb->SetVelocity(dir);
	}

	if (!m_isGrounded)
		animParam = L"playerJump";
	else if (m_isMoving)
		animParam = L"playerMove";
	else
		animParam = L"playerIdle";

	if (animParam != m_animator->GetCurrent()->GetName())
		m_animator->Play(animParam);
}

void Player::Jump()
{
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->SetVelocity({ rb->GetVelocity().x, -550.f });
	rb->SetGrounded(false);
}