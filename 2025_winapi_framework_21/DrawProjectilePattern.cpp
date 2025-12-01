#include "pch.h"
#include "DrawProjectilePattern.h"
#include "DOTweenCompo.h"
#include "Object.h"
#include "ProjectileManager.h"
#include "PlayerFindManager.h"

DrawProjectilePattern::DrawProjectilePattern(BossController* _controller,
	std::wstring _texture, std::wstring _sprite, float _delay, float _damage)
	: BossPattern(_controller),
	m_texture(_texture),
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
}

void DrawProjectilePattern::Update()
{
	m_projTime -= fDT;
	m_fireTime -= fDT;

	if (m_projTime <= 0.f && !m_isFireTime) {
		m_projTime = m_delay;
		m_projectiles.push(GET_SINGLE(ProjectileManager)
			->SpawnProjectile(Enemy, 65.f, m_brushObj->GetPos(), 0.f, 0.f));
	}

	if (m_fireTime <= 0.f)
	{
		m_isFireTime = true;
		auto* proj = m_projectiles.top();
		auto* dotween = proj->AddComponent<DOTweenCompo>();
		dotween->DOMove(m_player->GetPos(), 0.5f, EaseInCubic, [proj]()
			{
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
	brushObj->SetPos({ 100.f, WINDOW_HEIGHT - 200.f });
	dotweenCompo->DOLocalMoveY(-400.f, m_time, EaseLinear, [this]() {m_brushObj->SetDead(); });
	m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();

	BossPattern::SetUsed();
}
