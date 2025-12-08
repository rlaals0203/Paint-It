#pragma once
#include "UIElement.h"
class UIText :
    public UIElement
{

public:
    virtual void Render(HDC _hdc) override;
public:
    void SetText(const wstring& _text) { m_text = _text; }
    void SetTextColor(COLORREF color) { m_textColor = color; }
private:
    COLORREF m_textColor = RGB(255,255,255);
    wstring m_text;
};

