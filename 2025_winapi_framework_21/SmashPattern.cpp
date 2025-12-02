#include "pch.h"
#include "BossPattern.h"
#include "SmashPattern.h"
#include "BossController.h"
#include "ImpulseManager.h"
#include "DangerGizmo.h"
#include "ProjectileManager.h"
#include "EffectManager.h"
#include "SpriteObject.h"
#include "OilObject.h"

SmashPattern::SmashPattern(BossController* _controller) 
	: BossPattern(_controller), 
	m_dotween(nullptr),
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
	dangerGizmo->SetDangerGizmo(gizmoPos, { 500.f, 150.f }, 2.5f, 0.7f);

	m_state = State::Wait;
}

void SmashPattern::WaitState()
{
	m_delay -= fDT;
	if (m_delay > 0.f) return;

	Vec2 winSize = GET_WINDOWSIZE;
	Vec2 groundPos = { winSize.x / 2, winSize.y - 150 };
	m_dotween->DOMove(groundPos, 0.4f, EaseInExpo);

	m_state = State::Fall;
	m_delay = 0.4f;
}

void SmashPattern::FallState()
{
	m_delay -= fDT;
	if (m_delay > 0.f) return;

	Vec2 winSize = GET_WINDOWSIZE;
	GET_SINGLE(ImpulseManager)->ApplyImpulse(60.f, 0.5f);
	GET_SINGLE(EffectManager)->PlayEffect(EffectType::SmashSmoke, 
		{ winSize.x / 2, winSize.y - 400 }, { 10.f, 10.f }, 2.f);
	m_state = State::Ground;
}

void SmashPattern::GroundState()
{
	m_delay -= fDT;
	if (m_delay > 0.f) return;

	auto* drop = new SpriteObject(L"bullet", Layer::EFFECT);
	drop->SetSize({ 50.f, 50.f });
	drop->SetPos({ m_Controller->GetOwner()->GetPos() });

	auto* dotweenCompo = drop->AddComponent<DOTweenCompo>();
	float x = WINDOW_WIDTH * 0.05f + (rand() % (int)(WINDOW_WIDTH * 0.9f));
	float height = 300 + (rand() % 200);
	dotweenCompo->DOParabola({ x, WINDOW_HEIGHT - 100.f }, height, height * 0.003f, EaseOutSine, [drop]()
		{
			auto* oil = new OilObject(L"bullet", Layer::OIL);
			oil->SetPos({ drop->GetPos() });

			drop->SetDead();
		});

	if (--m_count <= 0)
		m_isUsed = false;

	m_delay = 0.02f;
}

void SmashPattern::SetUsed()
{
	if (m_dotween == nullptr)
		m_dotween = m_Controller->GetOwner()
		->GetComponent<DOTweenCompo>();

	Vec2 skyPos = { (float)(WINDOW_WIDTH / 2), -200.f };
	m_dotween->DOMove(skyPos, 1.f, EaseInBack);
	m_delay = 3;
	m_count = 6;
	m_state = State::Up;

	BossPattern::SetUsed();
}
