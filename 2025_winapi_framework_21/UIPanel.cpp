#include "pch.h"
#include "UIPanel.h"

UIPanel::UIPanel()
	: m_isActive(true)
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
	if (!m_isActive)
		return;

	Object::Update();

	for (UIElement* child : m_children)
	{
		child->Update();
	}
}

void UIPanel::Render(HDC _hdc)
{
	if (!m_isActive)
		return;
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