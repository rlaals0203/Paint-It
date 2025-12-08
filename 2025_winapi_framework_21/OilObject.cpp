#include "pch.h"
#include "OilObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Collider.h"

OilObject::OilObject(std::wstring _texture, Layer _layer) : SpriteObject(_texture, _layer, true)
{
	m_lifeTime = 20.f;

	SetSize({ 65.f, 60.f });
	auto* col = AddComponent<Collider>();
	col->SetSize({50.f, 50.f});
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, _layer);

	m_textures[0] = GET_SINGLE(ResourceManager)->GetTexture(L"oil1");
	m_textures[1] = GET_SINGLE(ResourceManager)->GetTexture(L"oil2");
	m_textures[2] = GET_SINGLE(ResourceManager)->GetTexture(L"oil31");

	int index = Random::Range(0, 2);
	m_isTrans = true;
	m_texture = m_textures[index];
}

OilObject::~OilObject()
{
}

void OilObject::Render(HDC _hdc)
{
	SpriteObject::Render(_hdc);
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
