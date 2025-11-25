#include "pch.h"
#include "BossPattern.h"
#include "SmashPattern.h"
#include "BossController.h"
#include "ImpulseManager.h"
#include "DangerGizmo.h"

SmashPattern::SmashPattern(BossController* _controller) 
	: BossPattern(_controller), 
	m_moveComponent(nullptr), 
	m_state(State::Up)
{
}

SmashPattern::~SmashPattern()
{
}

void SmashPattern::Update()
{
	switch (m_state)
	{
	case SmashPattern::State::Up: UpState();
		break;
	case SmashPattern::State::Wait: WaitState();
		break;
	case SmashPattern::State::Fall: FallState();
		break;
	default:
		break;
	}
}

void SmashPattern::UpState()
{
	auto* dangerGizmo = new DangerGizmo();
	Vec2 gizmoPos = { (float)(WINDOW_WIDTH / 2), (float)(WINDOW_HEIGHT)-175 };
	dangerGizmo->SetDangerGizmo(gizmoPos, { 500.f, 150.f }, 2.f, 1.f);

	m_state = State::Wait;
}

void SmashPattern::WaitState()
{
	m_delay -= fDT;
	if (m_delay < 0.f)
	{
		Vec2 groundPos = { (float)(WINDOW_WIDTH / 2), (float)(WINDOW_HEIGHT)-150 };
		Vec2 start = m_Controller->GetOwner()->GetPos();
		m_moveComponent->SetMove(start, groundPos, 0.3f);

		m_state = State::Fall;
		m_delay = 0.2f;
	}
}

void SmashPattern::FallState()
{
	m_delay -= fDT;
	if (m_delay < 0.f)
	{
		m_isUsed = false;
		GET_SINGLE(ImpulseManager)->ApplyImpulse(50.f, 0.3f);
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

	m_delay = 3.f;
	BossPattern::SetUsed();
}
