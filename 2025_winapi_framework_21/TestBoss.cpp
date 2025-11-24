#include "pch.h"
#include "TestBoss.h"
#include "TestPattern.h"
#include "MovePattern.h"
#include "Collider.h"
#include "EntityHealth.h"

TestBoss::TestBoss()
{
	AddModule(new TestPattern(m_Controller));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.20f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.50f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.80f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.30f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	AddModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.70f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	auto* col = AddComponent<Collider>();
	col->SetSize({ 125, 125 });
	auto* healthCompo = AddComponent<EntityHealth>();
	healthCompo->SetDefaultHP(10000.f);

}

TestBoss::~TestBoss()
{
}
