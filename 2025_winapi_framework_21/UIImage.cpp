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

	RECT rc = RECT_MAKE(pos.x, pos.y, size.x, size.y);

	::TransparentBlt(_hdc
		, pos.x
		, pos.y
		, size.x
		, size.y
		,m_image->GetTextureDC(),
		0, 0, m_width, m_height, RGB(255,0,255));
}

void UIImage::SetImage(wstring imageName)
{
	m_image = GET_SINGLE(ResourceManager)->GetTexture(imageName);
	if (m_image)
	{
		m_width = m_image->GetWidth();
		m_height = m_image->GetHeight();
	}
}
