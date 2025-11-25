#include "pch.h"
#include "UIElement.h"
#include "InputManager.h"

UIElement::UIElement() : m_state(UIState::NORMAL), m_isMouseOver(false)
{
}

UIElement::~UIElement()
{
}

void UIElement::CheckMouseOver()
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	POINT rawMousePos = GET_MOUSEPOS;
	Vec2 mousePos = Vec2(rawMousePos);

	RECT rect = RECT_MAKE(pos.x, pos.y, size.x, size.y);

	bool wasMouseOver = m_isMouseOver;
	m_isMouseOver = (mousePos.x >= rect.left &&
		mousePos.x <= rect.right &&
		mousePos.y >= rect.top &&
		mousePos.y <= rect.bottom);

	if (!wasMouseOver && m_isMouseOver)
	{
		OnMouseEnter();
		SetUIState(UIState::HOVER);
	}
	else if (wasMouseOver && !m_isMouseOver)
	{
		OnMouseExit();
		SetUIState(UIState::NORMAL);
	}

	if (m_isMouseOver && GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON))
	{
		OnMouseClick();
	}
}

void UIElement::Update()
{
	Object::Update();
}

void UIElement::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

