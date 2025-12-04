#include "pch.h"
#include "UIButton.h"
#include "InputManager.h"
#include "Texture.h"

UIButton::UIButton()
	: m_currentTexture(nullptr)
	, m_normalTexture(nullptr)
	, m_hoverTexture(nullptr)
	, m_pressedTexture(nullptr)
{
	SetSize({ 120.f, 40.f });
}

UIButton::~UIButton()
{
}

void UIButton::Update()
{
	UIText::Update();
	CheckMouseOver();
}

void UIButton::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	m_currentColor = RGB(0,0,0);
	m_currentTexture = nullptr;

	switch (m_state)
	{
	case UIState::NORMAL:
		SetTexture(m_normalTexture, m_normalColor);
		break;
	case UIState::HOVER:
		SetTexture(m_hoverTexture, m_hoverColor);
		break;
	case UIState::PRESSED:
		SetTexture(m_pressedTexture, m_pressedColor);
		break;
	}

	if (m_currentTexture)
	{
		int width = m_currentTexture->GetWidth();
		int height = m_normalTexture->GetHeight();

		Vec2 pos = GetPos();
		Vec2 size = GetSize();

		TransparentBlt(_hdc
			, pos.x
			, pos.y
			, size.x
			, size.y
			, m_currentTexture->GetTextureDC(),
			0, 0,
			width, height,
			RGB(255, 0, 255));

	}
	else
	{
		HBRUSH hBrush = CreateSolidBrush(m_currentColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, hBrush);

		RECT rect = RECT_MAKE(pos.x, pos.y, size.x, size.y);

		RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

		SelectObject(_hdc, oldBrush);
		DeleteObject(hBrush);
	}

	UIText::Render(_hdc);
}

void UIButton::SetAllTexture(Texture* normal, Texture* hover, Texture* pressed)
{
	m_normalTexture = normal;
	m_hoverTexture = hover;
	m_pressedTexture = pressed;
}

void UIButton::SetAllColor(COLORREF normalColor, COLORREF hoverColor, COLORREF pressedColor)
{
	m_normalColor = normalColor;
	m_hoverColor = hoverColor;
	m_pressedColor = pressedColor;
}

void UIButton::OnMouseClick()
{
	if (m_callback)
	{
		m_callback();
	}
}

void UIButton::SetTexture(Texture* texture, COLORREF color)
{
	if (texture)
	{
		m_currentTexture = texture;
	}
	else
	{
		m_currentTexture = nullptr;
		m_currentColor = color;
	}
}
