#include "pch.h"
#include "Platform.h"
#include "ResourceManager.h"
#include "DOTweenCompo.h"
#include "PlayerFindManager.h"

Platform::Platform(Vec2 _start, Vec2 _end) :
	SpriteObject(L"platform", Layer::PLATFORM, true)
{
	SetPos(_start);
	SetSize({ 300, 50 });
	m_collider = AddComponent<Collider>();
	m_collider->SetSize(GetSize());
	m_collider->SetName(L"Ground");
	m_collider->SetOffSetPos({ 0, -20 });

	auto* dotweenCompo = AddComponent<DOTweenCompo>();
	dotweenCompo->DOMove(_end, 1.f, EaseOutSine);

	m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();
}

Platform::~Platform()
{
}

void Platform::Render(HDC _hdc)
{
	SpriteObject::Render(_hdc);
}

void Platform::Update()
{
	int targetY = GetPos().y + 5;
	//m_collider->SetActive(m_player->GetPos().y > targetY);
}
