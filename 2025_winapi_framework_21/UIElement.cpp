#include "pch.h"
#include "UIElement.h"
#include "InputManager.h"

UIElement::UIElement() : m_state(UIState::NORMAL), m_isMouseOver(false)
{
}

UIElement::~UIElement()
{
}

void UIElement::Update()
{
	Object::Update();
	CheckMouseOver();
}

void UIElement::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void UIElement::CheckMouseOver()
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	POINT rawMousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vec2 mousePos = Vec2(rawMousePos.x, rawMousePos.y);

	bool wasMouseOver = m_isMouseOver;
	m_isMouseOver = (mousePos.x >= pos.x - size.x / 2 &&
		mousePos.x <= pos.x + size.x / 2 &&
		mousePos.y >= pos.y - size.y / 2 &&
		mousePos.y <= pos.y + size.y / 2);

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