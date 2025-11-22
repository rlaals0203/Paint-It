#include "pch.h"
#include "TestPattern.h"
#include "BossController.h"

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
		m_isUsed = false;
	}
}

void TestPattern::SetUsed()
{
	m_cooldownTimer = 0.f;
	m_cooldown = 2.f;
	BossPattern::SetUsed();
}
