#pragma once
#include "UIText.h"

class Texture;
class UIButton : public UIText
{
public:
	UIButton();
	virtual ~UIButton();

public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

public:
	void SetNomalColor(COLORREF color) { m_normalColor = color; }
	void SetHoverColor(COLORREF color) { m_hoverColor = color; }
	void SetPressedColor(COLORREF color) { m_pressedColor = color; }
	
	void SetNormalTexture(Texture* texture) { m_normalTexture = texture; }
	void SetHoverTexture(Texture* texture) { m_hoverTexture = texture; }
	void SetPressedTexture(Texture* texture) { m_pressedTexture = texture; }

public:
	void SetAllTexture(Texture* normal, Texture* hover, Texture* pressed);
	void SetAllColor(COLORREF normalColor, COLORREF hoverColor, COLORREF pressedColor);

public:
	void SetCallback(std::function<void()> _callback) { m_callback = _callback; }
	// std::function<void()> m_callback (함수를 담는 변수)

protected:
	virtual void OnMouseClick() override;

private:
	void SetTexture(Texture* texture, COLORREF color);

private:
	Texture* m_currentTexture;

	Texture* m_normalTexture;
	Texture* m_hoverTexture;
	Texture* m_pressedTexture;

	std::function<void()> m_callback = nullptr;

	COLORREF m_currentColor;

	COLORREF m_normalColor = RGB(100, 100, 100);
	COLORREF m_hoverColor = RGB(150, 150, 150);
	COLORREF m_pressedColor = RGB(50, 50, 50);
};