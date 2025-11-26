#include "pch.h"
#include "BossPattern.h"
#include "SmashPattern.h"
#include "BossController.h"
#include "ImpulseManager.h"
#include "DangerGizmo.h"
#include "ProjectileManager.h"

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
	case SmashPattern::State::Ground: GroundState();
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
		GET_SINGLE(ImpulseManager)->ApplyImpulse(60.f, 0.5f);
		m_state = State::Ground;
	}
}

void SmashPattern::GroundState()
{
	m_delay -= fDT;
	if (m_delay < 0.f)
	{
		if (--m_count <= 0)
			m_isUsed = false;

		int count = 16 + (m_count * 4);
		float angle = 360.f / (float)count;
		for (int i = 0; i < count; i++) {
			GET_SINGLE(ProjectileManager)->SpawnProjectile(
				ProjectileType::Enemy, 60.f,
				GetOwnerPos(), (m_count * 2.f) + angle * i, false,
				5.f + (m_count * 1.5f));
		}

		m_delay = 0.2f;
	}
}

void SmashPattern::SetUsed()
{
	if (m_moveComponent == nullptr)
		m_moveComponent = m_Controller->GetOwner()
		->GetComponent<MoveComponent>();

	Vec2 skyPos = { (float)(WINDOW_WIDTH / 2), -200.f };
	m_moveComponent->SetMove(GetOwnerPos(), skyPos, 2.f);
	m_delay = m_count = 3;
	m_state = State::Up;

	BossPattern::SetUsed();
}
