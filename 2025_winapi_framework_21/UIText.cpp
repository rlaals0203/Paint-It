#include "pch.h"
#include "UIText.h"

void UIText::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	RECT rect = RECT_MAKE(pos.x, pos.y, size.x, size.y);

	DrawText(_hdc, m_text.c_str(), -1, &rect,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
