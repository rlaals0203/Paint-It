#include "pch.h"
#include "UIPanel.h"

UIPanel::UIPanel()
{
}

UIPanel::~UIPanel()
{
	for (UIElement* child : m_children)
	{
		delete child;
	}
	m_children.clear();
}

void UIPanel::Update()
{
	Object::Update();

	for (UIElement* child : m_children)
	{
		child->Update();
	}
}

void UIPanel::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	HBRUSH hBrush = CreateSolidBrush(m_backgroundColor);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, hBrush);

	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

	SelectObject(_hdc, oldBrush);
	DeleteObject(hBrush);

	for (UIElement* child : m_children)
	{
		child->Render(_hdc);
	}

	UIElement::Render(_hdc);
}