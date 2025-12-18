#pragma once
#include "UIElement.h"

class UIPanel : public UIElement
{
public:
	UIPanel();
	virtual ~UIPanel();

public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

public:
	void SetBackgroundColor(COLORREF _color) { m_backgroundColor = _color; }

	template<typename T>
	T* AddUIElement()
	{
		static_assert(std::is_base_of<UIElement, T>::value, "UIElement로부터 상속받아야 함");
		T* element = new T();
		m_children.push_back(element);
		return element;
	}

public:
	void SetActive(bool active) { m_isActive = active; }

private:
	bool m_isActive;
	bool m_isEnd = false;

	vector<UIElement*> m_children;
	COLORREF m_backgroundColor = RGB(50, 50, 50);
};