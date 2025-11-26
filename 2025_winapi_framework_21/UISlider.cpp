#include "pch.h"
#include "UISlider.h"

UISlider::UISlider()
{
    m_minValue = 0.0f;
    m_maxValue = 1.0f;
    m_value = 0.5f;
    m_isDragging = false;
    SetSize({ 200.0f, 20.0f });
    SetPos({ 10.0f, 10.0f });
}

UISlider::~UISlider()
{
}

void UISlider::SetRange(float min, float max)
{
    m_minValue = min;
    m_maxValue = max;
    if (m_value < m_minValue) m_value = m_minValue;
    if (m_value > m_maxValue) m_value = m_maxValue;
}

void UISlider::SetValue(float value)
{
    float clamped = std::clamp(value, m_minValue, m_maxValue);
    if (m_value != clamped) {
        m_value = clamped;
        if (m_onValueChanged) m_onValueChanged(m_value);
    }
}

float UISlider::GetValue() const
{
    return m_value;
}

void UISlider::SetOnValueChanged(std::function<void(float)> callback)
{
    m_onValueChanged = callback;
}

void UISlider::Update()
{
    CheckMouseOver();
    if (m_isDragging) {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(GetActiveWindow(), &pt);
        float pos = static_cast<float>(pt.x) - GetPos().x;
        float newValue = PositionToValue(pos);
        SetValue(newValue);
    }
    UIElement::Update();
}

void UISlider::Render(HDC _hdc)
{
    Vec2 pos = GetPos();

    Vec2 size = GetSize();

    RECT rc
    {
        pos.x,
        pos.y,
        pos.x + size.x,
        pos.y + size.y
    };

    FillRect(_hdc, &rc, (HBRUSH)(COLOR_BTNFACE + 1));

    float handlePos = ValueToPosition(m_value);
    RECT handleRc = {
        (pos.x + handlePos) - 5,
        pos.y - 5,
        (pos.x + handlePos) + 5,
        (pos.y + size.y) + 5
    };
    FillRect(_hdc, &handleRc, (HBRUSH)(COLOR_HIGHLIGHT + 1));

    UIElement::Render(_hdc);
}

void UISlider::OnMouseClick()
{
    m_isDragging = true;
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(GetActiveWindow(), &pt);
    float pos = static_cast<float>(pt.x) - GetPos().x;
    float newValue = PositionToValue(pos);
    SetValue(newValue);
}

void UISlider::OnMouseEnter()
{

}

void UISlider::OnMouseExit()
{
    m_isDragging = false;
}

float UISlider::ValueToPosition(float value) const
{
    float barStart = 0.0f;
    float barEnd = GetSize().x;
    float t = (value - m_minValue) / (m_maxValue - m_minValue);
    return barStart + t * (barEnd - barStart);
}

float UISlider::PositionToValue(float pos) const
{
    float barStart = 0.0f;
    float barEnd = GetSize().x;
    float t = (pos - barStart) / (barEnd - barStart);
    t = std::clamp(t, 0.0f, 1.0f);
    return m_minValue + t * (m_maxValue - m_minValue);
}
