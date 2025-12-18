#include "pch.h"
#include "HealPack.h"
#include "Collider.h"
#include "EntityHealth.h"
#include "SceneManager.h"

HealPack::HealPack(std::wstring _texture, Layer _layer)
	: SpriteObject(_texture, _layer, true), 
	m_healAmount(25)
{
	AddComponent<Collider>();
	SetSize({ 100, 100 });
}

HealPack::~HealPack()
{
}

void HealPack::Render(HDC _hdc)
{
	SpriteObject::Render(_hdc);
}

void HealPack::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Player")
	{
		auto* health =_other->GetOwner()->GetComponent<EntityHealth>();
		if (health != nullptr)
			health->ApplyDamage(-m_healAmount, false);

		SetDead();
		GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(this);
	}
}
