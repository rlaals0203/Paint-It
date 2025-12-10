#include "pch.h"
#include "Boss.h"
#include "Animator.h"
#include "BossController.h"
#include "BossIdleModule.h"
#include "BossPatternModule.h"
#include "EntityHealth.h"
#include "SceneManager.h"

Boss::Boss() : Object(),
	m_controller(nullptr)
	, m_animator(nullptr)
{
	m_controller = AddComponent<BossController>();
	m_controller->SetOwner(this);
	m_controller->SetBoss();
	m_controller->AddModule(L"IdleModule", new BossIdleModule(m_controller));
	m_controller->AddModule(L"PatternModule", new BossPatternModule(m_controller));
	m_controller->ChangeModule(L"IdleModule");

	m_animator = AddComponent<Animator>();
	m_animator->SetOwner(this);
}

Boss::~Boss()
{
}

void Boss::Update()
{
	Object::Update();

	if (m_isBlinking != m_isBlink)
	{
		m_isBlinking = m_isBlink;
		m_animator->Play(m_isBlinking ? m_blinkName : m_animName);
	}
}

void Boss::GoStage(int stage)
{
	std::wstring sceneName = L"Stage" + std::to_wstring(stage);
	GET_SINGLE(SceneManager)->LoadScene(sceneName);
}

void Boss::GoTitle()
{
	GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
}

void Boss::SetAnimation(wstring animationKey)
{
	m_animator->Play(animationKey);
}

void Boss::StopAnimation()
{
	if (m_animator)
	{
		m_animator->Stop();
	}
}

void Boss::BossReset()
{
	BossPatternModule* patternMoudle = (BossPatternModule*)(m_controller->GetModule(L"PatternModule"));
	patternMoudle->BossReset();
}

void Boss::AddModule(BossPattern* addedPattern)
{
	BossPatternModule* patternMoudle = (BossPatternModule*)(m_controller->GetModule(L"PatternModule"));
	patternMoudle->AddPattern(addedPattern);
}

void Boss::AddMoveModule(MovePattern* addedPattern)
{
	BossPatternModule* patternMoudle = (BossPatternModule*)(m_controller->GetModule(L"PatternModule"));
	patternMoudle->AddMovePattern(addedPattern);
}

void Boss::ClearModule()
{
	BossPatternModule* patternMoudle = (BossPatternModule*)(m_controller->GetModule(L"PatternModule"));
	patternMoudle->ClearPattern();
}

