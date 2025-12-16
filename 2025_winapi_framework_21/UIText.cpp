#include "pch.h"
#include "UIText.h"
#include "ResourceManager.h"

UIText::UIText()
{
}

UIText::~UIText()
{
}

void UIText::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	RECT rect = RECT_MAKE(pos.x, pos.y, size.x, size.y);

	HFONT hFont = GET_SINGLE(ResourceManager)->GetFont(FontType::UI);

	HFONT hOldFont = (HFONT)SelectObject(_hdc, hFont);

	::SetTextColor(_hdc,m_textColor);
	SetBkMode(_hdc, TRANSPARENT);

	DrawText(_hdc, m_text.c_str(), -1, &rect,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(_hdc, hOldFont);

	UIElement::Render(_hdc);
}
