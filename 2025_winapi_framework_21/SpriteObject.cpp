#include "pch.h"
#include "SpriteObject.h"
#include "ResourceManager.h"
#include "SceneManager.h"

SpriteObject::SpriteObject(std::wstring _texture, Layer _layer, bool isTrans)
{
	_isTrans = isTrans;
	m_texture = GET_SINGLE(ResourceManager)->GetTexture(_texture);
	GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, _layer);
}

SpriteObject::~SpriteObject() { }

void SpriteObject::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	int width = m_texture->GetWidth();
	int height = m_texture->GetHeight();
    int x = (int)(pos.x - size.x / 2);
    int y = (int)(pos.y - size.y / 2);

    if (_isTrans)
    {
        ::TransparentBlt(
            _hdc,
            x, y,
            size.x, size.y,
            m_texture->GetTextureDC(),
            0, 0, width, height,
            RGB(255, 0, 255)
        );
    }
    else
    {
        ::StretchBlt(
            _hdc,
            x, y,
            size.x, size.y,
            m_texture->GetTextureDC(),
            0, 0, width, height,
            SRCCOPY
        );
    }
	ComponentRender(_hdc);
}
