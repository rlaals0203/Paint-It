#include "pch.h"
#include "PrismBoss.h"
#include "Collider.h"
#include "DOTweenCompo.h" 
#include "ResourceManager.h"
#include "MakePrismPattern.h"
#include "GuidedLaserPattern.h"
#include "ReflectLazerPattern.h"

#include "GuidedProjectilePattern.h"
#include "SmashPattern.h"
#include "LazerPattern.h"
#include "DrawProjectilePattern.h"

PrismBoss::PrismBoss() : Boss()
, m_animName(L"PrismBoss"), m_blinkName(L"PrismBossBlink"), m_shield(nullptr)

{
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(L"prismboss");
	m_blinkTexture = GET_SINGLE(ResourceManager)->GetTexture(L"firebossblink");

	auto* col = AddComponent<Collider>();
	col->SetSize({ 100, 100 });
	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetDefaultHP(10000.f);
	AddComponent<DOTweenCompo>();

	m_Animator->CreateAnimation(m_animName, m_texture,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);

	m_Animator->CreateAnimation(m_blinkName, m_blinkTexture,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);

	SetAnimation(m_animName);

	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.80f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.70f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.50f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.20f, WINDOW_HEIGHT * 0.20f }, 300.f, 0.5f));
	AddMoveModule(new MovePattern(m_Controller, { WINDOW_WIDTH * 0.30f, WINDOW_HEIGHT * 0.45f }, 300.f, 0.5f));

	//AddModule(new MakePrismPattern(m_Controller));
	//AddModule(new LazerPattern(m_Controller, 5));
	//AddModule(new GuidedLaserPattern(m_Controller, 10));
	AddModule(new ReflectLazerPattern(m_Controller, 10));
	//AddModule(new SmashPattern(m_Controller));
	//AddModule(new DrawProjectilePattern(m_Controller, L"knife", 0.075f, 10.f));
	//AddModule(new GuidedProjectilePattern(m_Controller, ProjectileType::Enemy, 0.4f, 10));
}

PrismBoss::~PrismBoss()
{
}

void PrismBoss::Update()
{
	Object::Update();

	if (m_hasBlinked != m_isBlink)
	{
		m_hasBlinked = m_isBlink;
		m_Animator->Play(m_hasBlinked ? m_blinkName : m_animName);
	}

	if (GetPrismCount() > 0 && m_isShieldMode == false)
	{
		m_healthCompo->SetActive(false);
		m_shield = new SpriteObject(L"bossshield", Layer::EFFECT);
		m_shield->SetSize({ 170.f, 170.f });
		m_isShieldMode = true;
	}
	else if(GetPrismCount() == 0 && m_isShieldMode)
	{
		m_healthCompo->SetActive(true);

		m_isShieldMode = false;
		if (m_shield != nullptr)
			m_shield->SetDead();
		m_shield = nullptr;
	}

	if (m_isShieldMode)
	{
		Vec2 pos = GetPos();
		pos.y += 20.f;
		m_shield->SetPos(pos);
	}
}

void PrismBoss::Render(HDC _hdc)
{
	Object::Render(_hdc);
	ComponentRender(_hdc);
}
