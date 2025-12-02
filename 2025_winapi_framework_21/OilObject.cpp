#include "pch.h"
#include "OilObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Collider.h"

OilObject::OilObject(std::wstring _texture, Layer _layer) : SpriteObject(_texture, _layer, true)
{
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(_texture);
	m_lifeTime = 20.f;

	SetSize({ 50.f, 10.f });
	auto* col = AddComponent<Collider>();
	col->SetSize({50.f, 50.f});
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, _layer);
}

OilObject::~OilObject()
{
}

void OilObject::Render(HDC _hdc)
{
	SpriteObject::Render(_hdc);
	Object::Render(_hdc);
	ComponentRender(_hdc);
}

void OilObject::Update()
{
	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.f) {
		SetDead();
	}
}

void OilObject::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Player")
	{
		auto* player = dynamic_cast<Player*>(_other->GetOwner());
		player->SetOiledTime(5.f);
		SetDead();
	}
}
