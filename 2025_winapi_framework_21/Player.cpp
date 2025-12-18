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
#include "BurstSkill.h"

Player::Player()
	: m_pTexture(nullptr),
	m_completedFire(false),
	m_completedPrism(false)
{
	AddComponent<Rigidbody>();
	auto* col = AddComponent<Collider>();
	col->SetName(L"Player");

	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetIsPlayer(false);
	m_healthCompo->SetIsPlayer(false);
	m_healthCompo->SetDefaultHP(75.f);
	m_healthCompo->SubscribeDeath([this]() {HandleDead(); });

	m_groundChecker = new GroundChecker();
	m_groundChecker->SubscribeGroundChange([this](bool isGround) {HandleIsGround(isGround); });
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(m_groundChecker, Layer::GROUNDCHECKER);
	GET_SINGLE(PlayerFindManager)->SetPlayer(this);

#pragma region  animation
	m_playerIdle = L"playerIdle";
	m_rplayerIdle = L"rplayerIdle";
	m_playerMove = L"playerMove";
	m_rplayerMove = L"rplayerMove";
	m_playerJump = L"playerJump";
	m_rPlayerJump = L"rplayerJump";
	m_bplayer = L"bplayer";
	m_brplayer = L"brplayer";

	m_blinkTexture = GET_SINGLE(ResourceManager)->GetTexture(L"playerblink");
	m_pTexture = GET_SINGLE(ResourceManager)->GetTexture(L"player");
	m_rpTexture = GET_SINGLE(ResourceManager)->GetTexture(L"rplayer");
	m_blinkTexture = GET_SINGLE(ResourceManager)->GetTexture(L"playerblink");
	m_rblinkTexture = GET_SINGLE(ResourceManager)->GetTexture(L"rplayerblink");
	m_animator = AddComponent<Animator>();

	m_animator->CreateAnimation(
		m_playerIdle, m_pTexture,
		{ 0.f,0.f }, { 64.f, 64.f },
		{ 64.f,0.f }, 8, 0.1f);

	m_animator->CreateAnimation(
		m_rplayerIdle, m_rpTexture,
		{ 0.f,0.f }, { 64.f, 64.f },
		{ 64.f,0.f }, 8, 0.1f);

	m_animator->CreateAnimation(
		m_playerMove, m_pTexture,
		{ 0.f,64.f }, { 64.f,64.f },
		{ 64.f,0.f }, 8, 0.04f);

	m_animator->CreateAnimation(
		m_rplayerMove, m_rpTexture,
		{ 0.f,64.f }, { 64.f,64.f },
		{ 64.f,0.f }, 8, 0.04f);

	m_animator->CreateAnimation(
		m_playerJump, m_pTexture,
		{ 0.f,128.f }, { 64.f,64.f },
		{ 64.f,0.f }, 8, 0.1f);

	m_animator->CreateAnimation(
		m_rPlayerJump, m_rpTexture,
		{ 0.f,128.f }, { 64.f,64.f },
		{ 64.f,0.f }, 8, 0.1f);

	m_animator->CreateAnimation(
		m_bplayer, m_blinkTexture,
		{ 0.f,0.f }, { 64.f, 64.f },
		{ 64.f,0.f }, 8, 0.1f);

	m_animator->CreateAnimation(
		m_brplayer, m_rblinkTexture,
		{ 0.f,0.f }, { 64.f, 64.f },
		{ 64.f,0.f }, 8, 0.1f);

	m_animator->Play(m_playerIdle);
#pragma endregion
}

Player::~Player()
{
	m_groundChecker = nullptr;
	m_animator = nullptr;
	m_healthCompo = nullptr;
}

void Player::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Player::Update()
{
	Object::Update();

	PlayerMovement();
	SetAnimationParam();
	ClampPlayer();
	SetGroundCheckerPos();

	if (m_isOiled)
	{
		m_oiledTime -= fDT;
		if (m_oiledTime <= 0.f)
		{
			m_isOiled = false;
			m_speed = 3.f;
		}
	}
}

void Player::SetAnimationParam()
{
	wstring animParam;

	if (!m_isGrounded)
		animParam = m_isRight ? m_rPlayerJump : m_playerJump;
	else if (m_isMoving)
		animParam = m_isRight ? m_rplayerMove : m_playerMove;
	else
		animParam = m_isRight ? m_rplayerIdle : m_playerIdle;

	if (m_isBlink)
		animParam = m_isRight ? m_bplayer : m_brplayer;

	if (animParam != m_animator->GetCurrent()->GetName())
		m_animator->Play(animParam);
}

void Player::FireProjectile()
{
	Vec2 playerPos = GetPos();
	Vec2 mousePos = GET_MOUSEPOS;
	Vec2 dir = mousePos - playerPos;
	dir.Normalize();

	float centerAngle = atan2f(dir.y, dir.x) * (180.f / PI);
	float angles[3] = { centerAngle, centerAngle - 10.f, centerAngle + 10.f };

	for (int i = 0; i < 3; i++)
	{
		if (m_completedFire)
		{
			int rand = Random::Range(0, 10);
			if (rand == 1)
			{
				GET_SINGLE(ProjectileManager)->SpawnProjectile(ProjectileType::PlayerRedBullet,
					50.f, playerPos, angles[i], 20.f, true);

				continue;
			}
		}

		GET_SINGLE(ProjectileManager)->SpawnProjectile(ProjectileType::PlayerProjectile,
			50.f, playerPos, angles[i], 20.f, true);
	}

	m_coolTime = m_delay;
}

void Player::PlayerMovement()
{
	Move();

	if (GET_KEY(KEY_TYPE::SPACE) && m_isGrounded)
		Jump();

	m_coolTime -= fDT;
	if (GET_KEY(KEY_TYPE::LBUTTON) && m_coolTime <= 0.f)
		FireProjectile();

	m_currentDashTime -= fDT;
	if (GET_KEYDOWN(KEY_TYPE::LSHIFT) && m_currentDashTime <= 0.f)
		Dash();
}

void Player::Dash()
{
	auto* rb = GetComponent<Rigidbody>();

	int direction = m_isRight ? 1 : -1;
	float power = m_isOiled ? 1000 : 3500;
	Vec2 dir = { (float)(direction * power), rb->GetVelocity().y};
	rb->SetVelocity(dir);

	m_currentDashTime = m_dashCoolTime;
}

void Player::Move()
{
	Vec2 dir = {};

	if (GET_KEY(KEY_TYPE::D))
		dir.x += m_speed;
	else if (GET_KEY(KEY_TYPE::A))
		dir.x -= m_speed;

	m_isRight = dir.x > 0;
	m_isMoving = fabs(dir.x) > 0.f;

	Translate({ dir.x * 100.f * fDT, dir.y * 100.f * fDT });
}

void Player::ClampPlayer()
{
	Vec2 pos = GetPos();
	float x = std::clamp(pos.x, 15.f, WINDOW_WIDTH - 15.f);
	float y = std::clamp(pos.y, 0.f, 720.f);
	SetPos({ x, y });
}

void Player::SetGroundCheckerPos()
{
	Vec2 pos = GetPos();
	pos.y += 40;
	m_groundChecker->SetPos(pos);
}

void Player::HandleIsGround(bool _isGround)
{
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->SetGrounded(_isGround);
	m_isGrounded = _isGround;
}

void Player::HandleDead()
{
	GET_SINGLE(SceneManager)->RequestLoadScene(L"GameOverScene");
}

void Player::Jump()
{
	Rigidbody* rb = GetComponent<Rigidbody>();
	rb->SetVelocity({ rb->GetVelocity().x, -550.f });
	rb->SetGrounded(false);
}