#include "pch.h"
#include "PrismBoss.h"
#include "Collider.h"
#include "DOTweenCompo.h" 
#include "ResourceManager.h"
#include "MakePrismPattern.h"
#include "GuidedLaserPattern.h"
#include "ReflectLazerPattern.h"
#include "SceneManager.h"
#include "LazerPattern.h"
#include "AroundLaserPattern.h"
#include "SkyLaserPattern.h"
#include "BossController.h"

PrismBoss::PrismBoss() : Boss(), 
	m_awakenName(L"PrismAwaken"),
	m_shield(nullptr),
	m_awakenMode(false),
	m_isChanging(false)
{
	m_animName = L"PrismBoss";
	m_blinkName = L"PrismBossBlink";
	m_awakenName = L"PrismAwaken";
	m_changingName = L"PrismChanging";

	m_texture = GET_SINGLE(ResourceManager)->GetTexture(L"prismboss");
	m_blinkTexture = GET_SINGLE(ResourceManager)->GetTexture(L"firebossblink");
	m_shieldTexture = GET_SINGLE(ResourceManager)->GetTexture(L"bossshield");

	auto* col = AddComponent<Collider>();
	col->SetSize({ 100, 100 });
	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetDefaultHP(300.f);
	AddComponent<DOTweenCompo>();

	m_animator->CreateAnimation(m_animName, m_texture,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);

	m_animator->CreateAnimation(m_awakenName, m_texture,
		{ 0.f, 96.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);

	m_animator->CreateAnimation(m_changingName, m_texture,
		{ 0.f, 48.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 10, 0.1f);

	m_animator->CreateAnimation(m_blinkName, m_blinkTexture,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);

	SetAnimation(m_animName);

	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.80f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.70f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.50f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.20f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_controller, { WINDOW_WIDTH * 0.30f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));

	AddModule(new MakePrismPattern(m_controller));
	AddModule(new LazerPattern(m_controller, 5));
	AddModule(new ReflectLazerPattern(m_controller, 10));
	AddModule(new AroundLaserPattern(m_controller, 10));
	AddModule(new SkyLaserPattern(m_controller, 10));
	AddModule(new GuidedLaserPattern(m_controller, 10));
}

PrismBoss::~PrismBoss()
{
}

void PrismBoss::Update()
{
	CheckAwaken();

	if (m_isChanging) {
		Changing();
		return;
	}

	Boss::Update();

	if (GetPrismCount() > 0 && m_isShieldMode == false)
		ActiveShield();
	else if (GetPrismCount() == 0 && m_isShieldMode)
		InActiveShield();

	if (m_isShieldMode)
		m_shield->SetPos(GetPos());
}

void PrismBoss::Render(HDC _hdc)
{
	Object::Render(_hdc);
	ComponentRender(_hdc);
}

void PrismBoss::ActiveShield()
{
	m_healthCompo->SetActive(false);
	m_shield = new BossShield();
	m_shield->SetSize({ 6.f, 6.f });
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(m_shield, Layer::SHIELD);
	m_isShieldMode = true;
}

void PrismBoss::InActiveShield()
{
	m_healthCompo->SetActive(true);

	m_isShieldMode = false;
	if (m_shield != nullptr)
		m_shield->SetDead();
	m_shield = nullptr;
}

void PrismBoss::CheckAwaken()
{
	if (!m_isChanging && !m_awakenMode)
	{
		int currrent = m_healthCompo->GetCurrentHp();
		int max = m_healthCompo->GetMaxHp();
		if ((float)currrent / max <= 0.3f)
		{
			m_isChanging = true;
			m_animator->Play(m_changingName);
		}
	}
}

void PrismBoss::Changing()
{
	m_changeTime -= fDT;
	if (m_changeTime <= 0.f)
	{
		m_isChanging = false;
		m_awakenMode = true;
		m_animator->Play(m_awakenName);
		m_animName = m_awakenName;
		ClearModule();
		AddAwakenPattern();
	}
}

void PrismBoss::AddAwakenPattern()
{
	//AddModule(new MakePrismPattern(m_controller));
	//AddModule(new AroundLaserPattern(m_controller, 15, true, 0.05f, 1.f));
	//AddModule(new SkyLaserPattern(m_controller, 6, true, 0.34f, 0.28f));
	//AddModule(new GuidedLaserPattern(m_controller, 20, true, 0.05f, 0.5f));
	AddModule(new ReflectLazerPattern(m_controller, 15, true, 0.07f, 0.5f));
}
