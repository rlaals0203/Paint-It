#include "pch.h"
#include "BossShield.h"
#include "ResourceManager.h"
#include "Collider.h"

BossShield::BossShield()
{
	m_animator = AddComponent<Animator>();
	auto* tex = GET_SINGLE(ResourceManager)->GetTexture(L"bossshield");
	m_animator->CreateAnimation(L"shield", tex,
		{ 0.f, 0.f }, { 48.f, 48.f },
		{ 48.f, 0.f }, 8, 0.1f);
	m_animator->Play(L"shield");

	auto* col = AddComponent<Collider>();
	col->SetSize(GetSize());
}

BossShield::~BossShield()
{
}

void BossShield::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void BossShield::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"proj")
	{
		_other->GetOwner()->SetDead();
	}
}
