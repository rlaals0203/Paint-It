#pragma once
#include "Object.h"

enum class UIState
{
	NORMAL,
	HOVER,
	PRESSED,
	DISABLED
};

class UIElement : public Object
{
public:
	UIElement();
	virtual ~UIElement();

public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

public:
	void SetUIState(UIState _state) { m_state = _state; }
	UIState GetUIState() const { return m_state; }

	bool IsMouseOver() const { return m_isMouseOver; }
	virtual void OnMouseEnter() {}
	virtual void OnMouseExit() {}
	virtual void OnMouseClick() {}

protected:
	virtual void CheckMouseOver();

protected:
	UIState m_state = UIState::NORMAL;
	bool m_isMouseOver = false;
};