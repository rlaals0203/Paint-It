#include "pch.h"
#include "TestBoss.h"
#include "TestPattern.h"
#include "Collider.h"
#include "EntityHealth.h"

TestBoss::TestBoss()
{
	AddModule(new TestPattern(m_Controller));
	auto* col = AddComponent<Collider>();
	col->SetSize({ 125, 125 });
	auto* healthCompo = AddComponent<EntityHealth>();
	healthCompo->SetDefaultHP(10000.f);

}

TestBoss::~TestBoss()
{
}
