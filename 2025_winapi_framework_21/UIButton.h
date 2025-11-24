#pragma once
#include "UIElement.h"

class UIButton : public UIElement
{
public:
	UIButton();
	virtual ~UIButton();

public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

public:
	void SetText(const wstring& _text) { m_text = _text; }
	void SetCallback(std::function<void()> _callback) { m_callback = _callback; }
	// std::function<void()> m_callback (함수를 담는 변수)

protected:
	virtual void OnMouseClick() override;

private:
	wstring m_text;
	std::function<void()> m_callback = nullptr;
	COLORREF m_normalColor = RGB(100, 100, 100);
	COLORREF m_hoverColor = RGB(150, 150, 150);
	COLORREF m_pressedColor = RGB(50, 50, 50);
};