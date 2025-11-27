#pragma once
#include "UIElement.h"
class UIText :
    public UIElement
{

public:
    virtual void Render(HDC _hdc) override;
public:
    void SetText(const wstring& _text) { m_text = _text; }
private:
    wstring m_text;
};

