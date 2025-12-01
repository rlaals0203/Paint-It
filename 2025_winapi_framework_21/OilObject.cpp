#include "pch.h"
#include "OilObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Collider.h"
#include "PlayerFindManager.h"

OilObject::OilObject(std::wstring _texture, Layer _layer) : SpriteObject(_texture, _layer, true)
{
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(_texture);
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, _layer);
	//m_player = GET_SINGLE(PlayerFindManager)->GetPlayer();
}

OilObject::~OilObject()
{
}

void OilObject::Render(HDC _hdc)
{
	SpriteObject::Render(_hdc);
}

void OilObject::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Player")
	{
		auto* player = dynamic_cast<Player*>(_other->GetOwner());
		player->SetOiledTime(3.f);
	}
}
