#include "pch.h"
#include "DrawProjectilePattern.h"
#include "DOTweenCompo.h"
#include "Object.h"
#include "SceneManager.h"

DrawProjectilePattern::DrawProjectilePattern(BossController* _controller,
	std::wstring _texture, std::wstring _sprite, float _delay, float _damage)
	: BossPattern(_controller),
	m_texture(_texture),
	m_sprite(_sprite),
	m_delay(_delay),
	m_damage(_damage),
	m_time(1.5f),
	m_brushObj(nullptr)
{
}

DrawProjectilePattern::~DrawProjectilePattern()
{
}

void DrawProjectilePattern::Update()
{
	m_projTime -= fDT;
	m_time -= fDT;

	if (m_projTime <= 0.f) {
		m_projTime = m_delay;
		auto* proj = new GuidedProjectile();
		proj->Init(m_texture, 100.f, m_damage, 5.f);
		proj->SetPos(m_brushObj->GetPos());
		proj->SetSize({ 50.f, 50.f });
		proj->SetStop();
		m_projectiles.push_back(proj);
		GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(proj, Layer::ENEMYPROJECTILE);
	}

	if (m_time <= 0.f)
	{
		for (auto proj : m_projectiles)
		{
			proj->SetPlay();
		}

		m_projectiles.clear();
		m_isUsed = false;
	}
}

void DrawProjectilePattern::SetUsed()
{
	m_time = 1.5f;
	m_projTime = m_delay;
	auto* brushObj = new SpriteObject(m_sprite);
	auto* dotweenCompo = brushObj->AddComponent<DOTweenCompo>();
	brushObj->SetSize({150.f, 150.f});
	brushObj->SetPos({ 100.f, WINDOW_HEIGHT - 200.f });

	m_brushObj = brushObj;
	dotweenCompo->DOLocalMoveY(-400.f, m_time, EaseLinear, [this]() {m_brushObj->SetDead(); });

	BossPattern::SetUsed();
}
