#include "pch.h"
#include "TestPattern.h"
#include "BossController.h"
#include "ProjectileManager.h"

TestPattern::TestPattern(BossController* _controller)
	:BossPattern(_controller)
	, m_cooldownTimer(0.f)
	, m_cooldown(2.f)
{

}

TestPattern::~TestPattern()
{

}

void TestPattern::Update()
{
	m_cooldownTimer += fDT;
	if (m_cooldownTimer >= m_cooldown) 
	{
		GET_SINGLE(ProjectileManager)->SpawnProjectile(Enemy, 20.f, 
			{ m_Controller->GetOwner()->GetPos()},
			90.f);
		m_isUsed = false;
	}
}

void TestPattern::SetUsed()
{
	m_cooldownTimer = 0.f;
	m_cooldown = 2.f;
	BossPattern::SetUsed();
}
