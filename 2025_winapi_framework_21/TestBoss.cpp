#include "pch.h"
#include "TestBoss.h"
#include "TestPattern.h"
#include "MovePattern.h"
#include "CircleProjectilePattern.h"
#include "Collider.h"
#include "ProjectileManager.h"
#include "EntityHealth.h"
#include "GuidedProjectilePattern.h"
#include "MoveComponent.h"
#include "SmashPattern.h"


TestBoss::TestBoss()
{
	auto* col = AddComponent<Collider>();
	col->SetSize({ 125, 125 });
	SetSize({ 250, 250 });
	auto* healthCompo = AddComponent<EntityHealth>();
	healthCompo->SetDefaultHP(10000.f);
	AddComponent<MoveComponent>();

	AddModule(new SmashPattern(m_Controller));
	AddModule(new GuidedProjectilePattern(m_Controller, ProjectileType::Enemy, 0.5f, 10));
	//AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 30));
	//AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.80f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	//AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 30));
	//AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.70f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	//AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 30));
	//AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 40));
	//AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.50f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	//AddModule(new CircleProjectilePattern(m_Controller, ProjectileType::Enemy, 40));
	//AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.20f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	//AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.30f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	//AddModule(new GuidedProjectilePattern(m_Controller, ProjectileType::Enemy, 0.5f, 10));
}

TestBoss::~TestBoss()
{
}
