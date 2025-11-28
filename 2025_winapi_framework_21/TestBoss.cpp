#include "pch.h"
#include "TestBoss.h"
#include "TestPattern.h"
#include "MovePattern.h"
#include "CircleProjectilePattern.h"
#include "Collider.h"
#include "ProjectileManager.h"
#include "EntityHealth.h"
#include "GuidedProjectilePattern.h"
#include "DOTweenCompo.h"
#include "SmashPattern.h"
#include "LazerPattern.h"


TestBoss::TestBoss() : Boss()
{
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(L"fireboss");
	auto* col = AddComponent<Collider>();
	col->SetSize({ 100, 100 });
	auto* healthCompo = AddComponent<EntityHealth>();
	healthCompo->SetDefaultHP(10000.f);

	m_Animator->CreateAnimation(L"FireBoss", m_texture,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);
	SetAnimation(L"FireBoss");
	AddComponent<DOTweenCompo>()->Init();
	AddModule(new SmashPattern(m_Controller));
	AddModule(new SmashPattern(m_Controller));
	AddModule(new LazerPattern(m_Controller, 5));
	AddModule(new LazerPattern(m_Controller, 5));
	AddModule(new GuidedProjectilePattern(m_Controller, ProjectileType::Enemy, 0.5f, 10));
	AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 30));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.80f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 30));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.70f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 30));
	AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 40));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.50f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 40));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.20f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.30f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	AddModule(new GuidedProjectilePattern(m_Controller, ProjectileType::Enemy, 0.5f, 10));
}

TestBoss::~TestBoss()
{
}

void TestBoss::Update()
{
	SetSize({ 4.f, 4.f });
	Object::Update();
}

void TestBoss::Render(HDC _hdc)
{
	Object::Render(_hdc);
	ComponentRender(_hdc);
}
