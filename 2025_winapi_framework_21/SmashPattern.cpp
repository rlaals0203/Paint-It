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
	Vec2 winSize = GET_WINDOWSIZE;
	Vec2 gizmoPos = { winSize.x / 2, winSize.y - 175 };
	dangerGizmo->SetDangerGizmo(gizmoPos, { 500.f, 150.f }, 2.f, 1.f);

	m_state = State::Wait;
}

void SmashPattern::WaitState()
{
	m_delay -= fDT;
	if (m_delay < 0.f)
	{
		Vec2 winSize = GET_WINDOWSIZE;
		Vec2 groundPos = { winSize.x / 2, winSize.y - 150 };
		m_moveComponent->SetMove(GetOwnerPos(), groundPos, 0.3f);

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
		GET_SINGLE(ImpulseManager)->ApplyImpulse(60.f, 0.4f);
	}
}

void SmashPattern::SetUsed()
{
	if (m_moveComponent == nullptr)
		m_moveComponent = m_Controller->GetOwner()
		->GetComponent<MoveComponent>();

	Vec2 skyPos = { (float)(WINDOW_WIDTH / 2), -200.f };
	m_moveComponent->SetMove(GetOwnerPos(), skyPos, 2.f);
	m_delay = 3.f;
	m_state = State::Up;

	BossPattern::SetUsed();
}
