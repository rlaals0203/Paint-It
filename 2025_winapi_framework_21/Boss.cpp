#include "pch.h"
#include "Boss.h"
#include "Animator.h"
#include "BossController.h"
#include "BossIdleModule.h"
#include "BossPatternModule.h"
#include "EntityHealth.h"

Boss::Boss() : Object(),
	m_Controller(nullptr)
	, m_Animator(nullptr)
{
	m_Controller = AddComponent<BossController>();
	m_Controller->SetOwner(this);
	m_Controller->SetBoss();
	m_Controller->AddModule(L"IdleModule", new BossIdleModule(m_Controller));
	m_Controller->AddModule(L"PatternModule", new BossPatternModule(m_Controller));
	m_Controller->ChangeModule(L"IdleModule");

	m_Animator = AddComponent<Animator>();
	m_Animator->SetOwner(this);
}

Boss::~Boss()
{
}

void Boss::SetAnimation(wstring animationKey)
{
	m_Animator->Play(animationKey);
}

void Boss::StopAnimation()
{
	if (m_Animator)
	{
		m_Animator->Stop();
	}
}

void Boss::ResetPattern()
{
	BossPatternModule* patternMoudle = (BossPatternModule*)(m_Controller->GetModule(L"PatternModule"));
	patternMoudle->PatternReset();
}

void Boss::AddModule(BossPattern* addedPattern)
{
	BossPatternModule* patternMoudle = (BossPatternModule*)(m_Controller->GetModule(L"PatternModule"));
	patternMoudle->AddPattern(addedPattern);
}
