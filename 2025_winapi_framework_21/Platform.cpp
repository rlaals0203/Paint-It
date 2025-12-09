#include "pch.h"
#include "Platform.h"
#include "ResourceManager.h"
#include "DOTweenCompo.h"

Platform::Platform(Vec2 _start, Vec2 _end) :
	SpriteObject(L"platform", Layer::PLATFORM, true)
{
	SetPos(_start);
	SetSize({ 200, 100 });
	m_collider = AddComponent<Collider>();
	m_collider->SetSize({GetSize().x, 10.f});
	m_collider->SetName(L"Ground");

	auto* dotweenCompo = AddComponent<DOTweenCompo>();
	dotweenCompo->DOMove(_end, 1.f, EaseOutSine);
}

Platform::~Platform()
{
}

void Platform::Render(HDC _hdc)
{
	SpriteObject::Render(_hdc);
}
