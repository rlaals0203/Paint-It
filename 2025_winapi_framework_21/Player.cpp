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

	if (GET_KEY(KEY_TYPE::F) && m_coolTime < 0.f)
	{
		CreateProjectile();	
	}

	if (GET_KEYDOWN(KEY_TYPE::LSHIFT))
	{
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vec2 velo = rb->GetVelocity();
		int force = m_isRight ? 1 : -1;
		Vec2 dir = { (float)(force * 2500), velo.y };
		rb->SetVelocity(dir);
	}
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
	m_coolTime = m_stat.delay;
	Vec2 offset = {-45.f, -45.f};

	for (int i = 0; i < 3; i++)
	{
		Projectile* proj = new Projectile;
		Vec2 pos = GetPos();
		proj->SetPos(pos);
		proj->SetSize({ 20.f,20.f });
		Vec2 mousePos = GET_MOUSEPOS;
		Vec2 dir = mousePos - pos;	
		offset.x += 45.f;
		offset.y += 45.f;
		proj->SetDir(dir + offset);

		GET_SINGLE(SceneManager)->GetCurScene()
			->AddObject(proj, Layer::PROJECTILE);
	}
}
