#include "pch.h"
#include "TestBoss.h"
#include "TestPattern.h"
#include "MovePattern.h"
#include "Collider.h"
#include "EntityHealth.h"

TestBoss::TestBoss()
{
	AddModule(new TestPattern(m_Controller));
	AddModule(new MovePattern(m_Controller,{0,0},10.f,0.5f));
	auto* col = AddComponent<Collider>();
	col->SetSize({ 125, 125 });
	auto* healthCompo = AddComponent<EntityHealth>();
	healthCompo->SetDefaultHP(10000.f);

}

TestBoss::~TestBoss()
{
}
