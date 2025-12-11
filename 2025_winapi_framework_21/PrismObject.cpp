#include "pch.h"
#include "PrismObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Collider.h"

PrismObject::PrismObject(Vec2 _pos, PrismBoss* _boss)
{
	m_boss = _boss;
	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetDefaultHP(30);
	m_healthCompo->SubscribeHealthThreshold([this]() {OnDead(); }, 0.f);
	AddComponent<Collider>();
	SetPos(_pos);
	SetSize({ 2.f, 2.f });
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::ENEMY);

	auto* texture = GET_SINGLE(ResourceManager)->GetTexture(L"prismboss");
	m_animator = AddComponent<Animator>();
	m_animator->CreateAnimation(L"prismObj", texture,
		{ 0.f, 48.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 10, 0.1f);

	m_animator->Play(L"prismObj");
}

PrismObject::~PrismObject()
{
}

void PrismObject::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void PrismObject::OnDead()
{
	GET_SINGLE(ResourceManager)->Play(L"prismbreak");
	m_boss->RemovePrism();
}
