#include "pch.h"
#include "PrismObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Collider.h"

PrismObject::PrismObject(Vec2 _pos, PrismBoss* _boss)
	: SpriteObject(L"prismcrystal", Layer::ENEMY)
{
	m_boss = _boss;
	m_healthCompo = AddComponent<EntityHealth>();
	m_healthCompo->SetDefaultHP(60);
	m_healthCompo->SubscribeDeath([this]() {OnDead(); });
	AddComponent<Collider>();
	SetPos(_pos);
	SetSize({ 50.f, 50.f });

	auto* texture = GET_SINGLE(ResourceManager)->GetTexture(L"prismcrystal");
}

PrismObject::~PrismObject()
{
}

void PrismObject::Render(HDC _hdc)
{
	SpriteObject::Render(_hdc);
	ComponentRender(_hdc);
}

void PrismObject::OnDead()
{
	GET_SINGLE(ResourceManager)->Play(L"prismbreak");
	m_boss->RemovePrism();
}
