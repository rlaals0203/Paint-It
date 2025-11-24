#include "pch.h"
#include "UIButton.h"

UIButton::UIButton()
{
	SetSize({ 120.f, 40.f });
}

UIButton::~UIButton()
{
}

void UIButton::Update()
{
	UIElement::Update();
}

void UIButton::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	COLORREF color = m_normalColor;
	switch (m_state)
	{
	case UIState::NORMAL:
		color = m_normalColor;
		break;
	case UIState::HOVER:
		color = m_hoverColor;
		break;
	case UIState::PRESSED:
		color = m_pressedColor;
		break;
	}

	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, hBrush);

	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

	SelectObject(_hdc, oldBrush);
	DeleteObject(hBrush);

	UIElement::Render(_hdc);
}

void UIButton::OnMouseClick()
{
	if (m_callback)
	{
		m_callback();
	}
}