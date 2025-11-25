#include "pch.h"
#include "BossPattern.h"
#include "SmashPattern.h"
#include "BossController.h"
#include "DangerGizmo.h"

SmashPattern::SmashPattern(BossController* _controller) 
	: BossPattern(_controller),  m_moveComponent(nullptr)
{
}

SmashPattern::~SmashPattern()
{
}

void SmashPattern::Update()
{
	if (!m_isPlaying) return;
	m_phase1 -= fDT;
	if (m_phase1 < 0.f && m_isPhase1)
	{
		m_isPhase1 = false;
		Vec2 pos = { (float)(WINDOW_WIDTH / 2), (float)(WINDOW_HEIGHT) - 50 };
		Vec2 start = m_Controller->GetOwner()->GetPos();
		m_moveComponent->SetMove(start, pos, 1.f);
	}
}

void SmashPattern::SetUsed()
{
	if (m_moveComponent == nullptr)
		m_moveComponent = m_Controller->GetOwner()
		->GetComponent<MoveComponent>();

	Vec2 skyPos = { (float)(WINDOW_WIDTH / 2), -200.f };
	Vec2 start = m_Controller->GetOwner()->GetPos();
	m_moveComponent->SetMove(start, skyPos, 2.f);

	auto* dangerGizmo = new DangerGizmo();
	Vec2 gizmoPos = { (float)(WINDOW_WIDTH / 2), (float)(WINDOW_HEIGHT) - 100 };
	dangerGizmo->SetDangerGizmo(gizmoPos, { 500.f, 200.f }, 2.f, 1.f);

	m_phase1 = 3.f;
	m_phase2 = 3.f;
	m_isPlaying = true;
	m_isPhase1 = true;
}
