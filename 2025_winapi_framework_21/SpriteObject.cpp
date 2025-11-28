#include "pch.h"
#include "SpriteObject.h"
#include "ResourceManager.h"

SpriteObject::SpriteObject(std::wstring _texture)
{
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(_texture);
}

SpriteObject::~SpriteObject() { }

void SpriteObject::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	int width = m_texture->GetWidth();
	int height = m_texture->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x, size.y,
		m_texture->GetTextureDC(),
		0, 0, width, height, RGB(255, 0, 255));
	ComponentRender(_hdc);
}
