#include "pch.h"
#include "FireBoss.h"
#include "MovePattern.h"
#include "CircleProjectilePattern.h"
#include "Collider.h"
#include "ProjectileManager.h"
#include "EntityHealth.h"
#include "GuidedProjectilePattern.h"
#include "DOTweenCompo.h"
#include "SmashPattern.h"
#include "LazerPattern.h"
#include "DrawProjectilePattern.h"


FireBoss::FireBoss() : Boss()
	, m_animName(L"FireBoss"), m_blinkName(L"FireBossBlink")
{
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(L"fireboss");
	m_blinkTexture = GET_SINGLE(ResourceManager)->GetTexture(L"firebossblink");

	auto* col = AddComponent<Collider>();
	col->SetSize({ 100, 100 });
	auto* healthCompo = AddComponent<EntityHealth>();
	healthCompo->SetDefaultHP(10000.f);
	AddComponent<DOTweenCompo>();

	m_Animator->CreateAnimation(m_animName, m_texture,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);

	m_Animator->CreateAnimation(m_blinkName, m_blinkTexture,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);

	SetAnimation(m_animName);

	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.80f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.70f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.50f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.20f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.30f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));

	AddModule(new SmashPattern(m_Controller));
	AddModule(new DrawProjectilePattern(m_Controller, L"knife", 0.075f, 10.f));
	AddModule(new LazerPattern(m_Controller, 5));
	AddModule(new GuidedProjectilePattern(m_Controller, ProjectileType::Enemy, 0.4f, 10));
	AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 30));
}

FireBoss::~FireBoss()
{
}

void FireBoss::Update()
{
	Object::Update();

	if (m_hasBlinked != m_isBlink)
	{
		m_hasBlinked = m_isBlink;
		m_Animator->Play(m_hasBlinked ? m_blinkName : m_animName);
	}
}

void FireBoss::Render(HDC _hdc)
{
	Object::Render(_hdc);
	ComponentRender(_hdc);
}
