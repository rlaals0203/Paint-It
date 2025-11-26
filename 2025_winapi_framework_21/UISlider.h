#pragma once
#include "UIElement.h"
class UISlider :
    public UIElement
{
public:
    UISlider();
    virtual ~UISlider();

public:
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;

public:
    virtual void OnMouseClick() override;
    virtual void OnMouseEnter() override;
    virtual void OnMouseExit() override;

public:
    void SetRange(float min, float max);
    void SetValue(float value);
    float GetValue() const;

public:
    void SetOnValueChanged(std::function<void(float)> callback);

private:
    float ValueToPosition(float value) const;
    float PositionToValue(float pos) const;

private:
    float m_minValue = 0.0f;
    float m_maxValue = 1.0f;
    float m_value = 0.5f;

    bool m_isDragging = false;
    std::function<void(float)> m_onValueChanged;
};

