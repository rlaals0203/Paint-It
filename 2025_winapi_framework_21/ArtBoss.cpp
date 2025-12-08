#include "pch.h"
#include "ArtBoss.h"
#include "Collider.h"
#include "DOTweenCompo.h" 
#include "ResourceManager.h"
#include "ReflectLazerPattern.h"

ArtBoss::ArtBoss()
{
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(L"prismboss");
	m_blinkTexture = GET_SINGLE(ResourceManager)->GetTexture(L"firebossblink");

	m_animName = L"PrismBoss";
	m_blinkName = L"PrismBossBlink";

	m_animator->CreateAnimation(m_animName, m_texture,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);

	m_animator->CreateAnimation(m_blinkName, m_blinkTexture,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);

	SetAnimation(m_animName);

	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.80f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.70f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.50f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.20f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.30f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));

	AddModule(new ReflectLazerPattern(m_controller, 10));

	auto* col = AddComponent<Collider>();
	col->SetSize({ 100, 100 });
	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetDefaultHP(300.f);
	AddComponent<DOTweenCompo>();
}

ArtBoss::~ArtBoss()
{
	Boss::Update();
}

void ArtBoss::Update()
{
}

void ArtBoss::Render(HDC _hdc)
{
	Object::Render(_hdc);
	ComponentRender(_hdc);
}
