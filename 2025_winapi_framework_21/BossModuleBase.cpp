#include "pch.h"
#include "BossModuleBase.h"
#include "Boss.h"
#include "BossController.h"

BossModuleBase::BossModuleBase(BossController* _controller)
 	: m_Active(false)
	, m_AnimationKey(L"")
{
	m_Controller = _controller;
}

BossModuleBase::~BossModuleBase()
{
}

void BossModuleBase::EnterModule()
{
	m_Active = true;
}

void BossModuleBase::UpdateModule()
{
	cout << "SD";
	if (m_AnimationKey != L"")
	{
		m_Controller->GetBoss()->SetAnimation(m_AnimationKey);
	}
}

void BossModuleBase::ExitModule()
{
	m_Active = false;
	m_Controller->GetBoss()->StopAnimation();
}

void BossModuleBase::SetAnimationKey(wstring _key)
{
	m_AnimationKey = _key;
}
