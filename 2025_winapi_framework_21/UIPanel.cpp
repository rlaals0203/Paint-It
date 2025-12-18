#include "pch.h"
#include "UIPanel.h"

UIPanel::UIPanel()
	: m_isActive(true)
{
}

UIPanel::~UIPanel()
{
	m_isEnd = true;
	for (UIElement* child : m_children)
	{
		delete child;
	}
	m_children.clear();
}

void UIPanel::Update()
{
    if (!m_isActive || m_isEnd)
        return;

    auto iter = m_children.begin();
    while (iter != m_children.end())
    {
        if ((*iter)->GetIsDead())
        {
            delete (*iter);
            iter = m_children.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    if (m_isEnd)
        return;

    Object::Update();

    if (m_isEnd)
        return;

    for (size_t i = 0; i < m_children.size(); ++i)
    {
        if (m_isEnd)
            return;

        if (m_children[i])
        {
            m_children[i]->Update();
        }
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