#include "pch.h"
#include "SkullProjectile.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Animation.h"
#include "Collider.h"
#include "PlayerFindManager.h"
#include "EffectManager.h"
#include "ImpulseManager.h"

SkullProjectile::SkullProjectile() : m_isExplosed(false)
{
	m_skullName = L"skullprojectile";
	m_rskullName = L"rskullprojectile";
	m_bskullName = L"bskullprojectile";
	m_rbskullName = L"rbskullprojectile";

	m_pTexture = GET_SINGLE(ResourceManager)->GetTexture(L"skull");
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::ENEMY);
	m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();

	auto* col = AddComponent<Collider>();
	col->SetSize({ 20, 20 });

	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetDefaultHP(40.f);
	m_lifeTime = 8.f;

	SetSize({ 2, 2 });

	m_animator = AddComponent<Animator>();
	m_animator->CreateAnimation(
		m_skullName, m_pTexture,
		{ 0.f,0.f }, { 32.f, 32.f },
		{ 32.f,0.f }, 3, 0.1f);

	m_animator->CreateAnimation(
		m_rskullName, m_pTexture,
		{ 0.f,32.f }, { 32.f, 32.f },
		{ 32.f,0.f }, 3, 0.1f);

	m_animator->CreateAnimation(
		m_bskullName, m_pTexture,
		{ 0.f,96.f }, { 32.f, 32.f },
		{ 32.f,0.f }, 1, 0.1f);

	m_animator->CreateAnimation(
		m_rbskullName, m_pTexture,
		{ 0.f,128.f }, { 32.f, 32.f },
		{ 32.f,0.f }, 1, 0.1f);

	m_animator->Play(m_skullName);
}

SkullProjectile::~SkullProjectile()
{
}

void SkullProjectile::Init(float _speed, float _damage, float _lifeTime)
{
	m_speed = _speed;
	m_damage = _damage;
	m_lifeTime = _lifeTime;
}

void SkullProjectile::Update()
{
	m_isRight = m_player->GetPos().x > GetPos().x;

	Vec2 dir = (m_player->GetPos() - GetPos());
	dir.Normalize();
	Translate({ dir.x * m_speed * 100 * fDT,  dir.y * m_speed * 100 * fDT });

	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.f && m_isExplosed == false) {
		Explosion();
	}

	if (m_isExplosed) {
		m_deadTime -= fDT;
		if (m_deadTime <= 0.f) {
			SetDead();
			GET_SINGLE(SceneManager)->RequestDestroy(this);
		}
	}
	else
	{
		wstring animParam;
		animParam = m_isRight ? m_rskullName : m_skullName;

		if (m_isBlink)
			animParam = m_isRight ? m_rbskullName : m_bskullName;

		if (animParam != m_animator->GetCurrent()->GetName())
			m_animator->Play(animParam);
	}

	Object::Update();
}

void SkullProjectile::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void SkullProjectile::EnterCollision(Collider* _other)
{
}

void SkullProjectile::Explosion()
{
	m_isExplosed = true;
	GET_SINGLE(EffectManager)->PlayEffect(EffectType::FireExplosion, GetPos(), { 5, 5 }, 1.f);
	GET_SINGLE(ImpulseManager)->ApplyImpulse(10.f, 0.2f);
	m_animator->Stop();
}
