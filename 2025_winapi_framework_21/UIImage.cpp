#include "pch.h"
#include "UIImage.h"
#include "ResourceManager.h"

UIImage::UIImage()
	: m_image(nullptr)
	, m_width(0)
	, m_height(0)
{
}

UIImage::~UIImage()
{
}

void UIImage::Render(HDC _hdc)
{
	if (!m_image)
	{
		UIElement::Render(_hdc);
		return;
	}

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	//RECT rc = RECT_MAKE(pos.x, pos.y, size.x, size.y);

	::TransparentBlt(_hdc
		, pos.x 
		, pos.y 
		, size.x
		, size.y
		,m_image->GetTextureDC(),
		0, 0, m_width, m_height, RGB(255,0,255));
}

void UIImage::SetPos(Vec2 pos)
{
	m_pos = pos;
	Vec2 size = GetSize();
	Vec2 setPos = pos;
	setPos.x = m_pos.x - size.x / 2;
	setPos.y = m_pos.y - size.y / 2;
	Object::SetPos(setPos);
}

void UIImage::SetSize(Vec2 size)
{
	Object::SetSize(size);

	Vec2 pos = GetPos();
	Vec2 setPos = pos;
	setPos.x = m_pos.x - size.x / 2;
	setPos.y = m_pos.y - size.y / 2;
	Object::SetPos(setPos);
}

void UIImage::SetImage(Texture* image)
{
	m_image = image;
	if (m_image)
	{
		m_width = m_image->GetWidth();
		m_height = m_image->GetHeight();
	}
}
