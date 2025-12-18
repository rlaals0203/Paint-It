#include "pch.h"
#include "DrawProjectilePattern.h"
#include "DOTweenCompo.h"
#include "Object.h"
#include "ProjectileManager.h"
#include "PlayerFindManager.h"
#include "EffectManager.h"
#include "ImpulseManager.h"

DrawProjectilePattern::DrawProjectilePattern(BossController* _controller,
	std::wstring _sprite, float _delay, float _damage)
	: BossPattern(_controller),
	m_sprite(_sprite),
	m_delay(_delay),
	m_damage(_damage),
	m_time(0.5f),
	m_fireTime(1.f),
	m_brushObj(nullptr),
	m_isFireTime(false)
{
}

DrawProjectilePattern::~DrawProjectilePattern()
{
	while (!m_projectiles.empty())
	{
		auto* proj = m_projectiles.top();
		m_projectiles.pop();
		if (proj && !proj->GetIsDead())
			proj->SetDead();
	}

	m_brushObj = nullptr;
}

void DrawProjectilePattern::Update()
{
	m_projTime -= fDT;
	m_fireTime -= fDT;

	if (m_projTime <= 0.f && !m_isFireTime) {
		m_projTime = m_delay;
		Vec2 pos = m_brushObj->GetPos();
		pos.y += 50;
		m_projectiles.push(GET_SINGLE(ProjectileManager)
			->SpawnProjectile(DrawProjectile, 40.f, pos, 0.f, 0.f));
	}

	if (m_fireTime <= 0.f)
	{
		m_isFireTime = true;
		auto* proj = m_projectiles.top();
		auto* dotween = proj->AddComponent<DOTweenCompo>();
		dotween->DOMove(m_player->GetPos(), 0.4f, EaseInCubic, [proj]()
			{
				GET_SINGLE(EffectManager)->PlayEffect(EffectType::FireExplosion, 
				proj->GetPos(), { 3.f, 3.f }, 0.9f);
				GET_SINGLE(ImpulseManager)->ApplyImpulse(10.f, 0.5f);
				proj->SetDead();
			});

		m_fireTime = 0.15f;
		m_projectiles.pop();

		if (m_projectiles.size() == 0)
			m_isUsed = false;
	}
}

void DrawProjectilePattern::SetUsed()
{
	m_isFireTime = false;
	m_time = m_fireTime =1.f;
	m_projTime = m_delay;
	auto* brushObj = m_brushObj = new SpriteObject(m_sprite, Layer::EFFECT);
	auto* dotweenCompo = brushObj->AddComponent<DOTweenCompo>();
	brushObj->SetSize({150.f, 150.f});
	brushObj->SetPos({ -100, WINDOW_HEIGHT / 4 });
	dotweenCompo->DOLocalMoveX(1400.f, m_time, EaseLinear, [this]() {m_brushObj->SetDead(); });
	m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();

	BossPattern::SetUsed();
}
