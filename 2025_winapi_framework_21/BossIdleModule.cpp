#include "pch.h"
#include "BossIdleModule.h"
#include "BossController.h"

BossIdleModule::BossIdleModule(BossController* controller)
	: BossModuleBase(controller)
	, m_cooldownTimer(0.f)
	, m_cooldown(0.f)
	, m_minCooldown(0.3f)
	, m_maxCooldown(1.2f)
{

}

BossIdleModule::~BossIdleModule()
{
}

void BossIdleModule::EnterModule()
{
	m_cooldown = (float)(rand() % ((m_maxCooldown - m_minCooldown) * 100) + m_minCooldown * 100) / 100.f;
	m_cooldownTimer = 0.f;

	BossModuleBase::EnterModule();
}

void BossIdleModule::UpdateModule()
{
	m_cooldownTimer += fDT;
	if (m_cooldownTimer >= m_cooldown) 
	{
		m_Controller->ChangeModule(L"PatternModule");
	}
}

void BossIdleModule::ExitModule()
{
	BossModuleBase::ExitModule();
}
