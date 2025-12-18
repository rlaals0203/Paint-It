#include "pch.h"
#include "ArtBoss.h"
#include "Collider.h"
#include "DOTweenCompo.h" 
#include "ResourceManager.h"
#include "BlackHolePattern.h"
#include "StringArtPattern.h"
#include "OriginPointPattern.h"
#include "DotBombPattern.h"

ArtBoss::ArtBoss()
	: m_roomPattern(nullptr)
{
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(L"artboss");
	m_blinkTexture = GET_SINGLE(ResourceManager)->GetTexture(L"artbossblink");

	m_animName = L"ArtmBoss";
	m_blinkName = L"ArtBossBlink";

	m_animator->CreateAnimation(m_animName, m_texture,
		{ 0.f, 0.f }, { 64.f, 64.f },
		{ 64.f, 0.f }, 8, 0.1f);

	m_animator->CreateAnimation(m_blinkName, m_blinkTexture,
		{ 0.f, 0.f }, { 64.f, 64.f },
		{ 64.f, 0.f }, 2, 1.f);

	SetAnimation(m_animName);

	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.80f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.70f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.50f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.20f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.30f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));

	AddModule(new BlackHolePattern(m_controller, 300));
	AddModule(new StringArtPattern(m_controller, 0.12f));
	AddModule(new OriginPointPattern(m_controller, 40));
	AddModule(new DotBombPattern(m_controller, 18));

	auto* col = AddComponent<Collider>();
	col->SetSize({ 100, 100 });
	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetDefaultHP(2800.f);
	m_healthCompo->SubscribeHealthThreshold([this]() { HandlePhase(); }, 0.3f);
	m_healthCompo->SubscribeDeath([this]() { GoStage(4); });
	AddComponent<DOTweenCompo>();
}

ArtBoss::~ArtBoss()
{
	if (m_roomPattern)
	{
		delete m_roomPattern;
		m_roomPattern = nullptr;
	}
}

void ArtBoss::Update()
{
	Boss::Update();
	if (m_roomPattern)
		m_roomPattern->Update();
}

void ArtBoss::Render(HDC _hdc)
{
	Object::Render(_hdc);
	ComponentRender(_hdc);
}

void ArtBoss::HandlePhase()
{
	if (m_roomPattern)
	{
		delete m_roomPattern;
		m_roomPattern = nullptr;
	}

	m_roomPattern = new ColorRoomPattern(1.f);
}