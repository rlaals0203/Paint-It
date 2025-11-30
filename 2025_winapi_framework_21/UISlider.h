#pragma once
#include "UIElement.h"

class Texture;
class UISlider : public UIElement
{
public:
    UISlider();
    virtual ~UISlider();

public:
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

public:
    void SetRange(float minVal, float maxVal)
    {
        m_min = minVal;
        m_max = maxVal;
    }

public:
    void SetValue(float value);
    float GetValue() const { return m_value; }

public:
    void SetTrackTexture(Texture* tex) { m_trackTex = tex; }
    void SetThumbTexture(Texture* tex) { m_thumbTex = tex; }

public:
    void SetFillColor(COLORREF color) { m_fillColor = color; }


protected:
    virtual void OnMouseDown();
    virtual void OnMouseUp();
    virtual void OnMouseDrag(POINT mousePos);

public:
    virtual void OnMouseClick() override;
    virtual void CheckMouseOver() override;

public:
    void SetCallback(std::function<void(float)> callback) { m_callback = callback; }

private:
    float ValueFromPos(int x);
    int PosFromValue(float value);

private:
    std::function<void(float)> m_callback = nullptr;

private:

    Texture* m_trackTex = nullptr;
    Texture* m_thumbTex = nullptr;

    COLORREF m_fillColor = RGB(80, 160, 255);

    bool m_dragging = false;

    RECT m_trackRect = { 0 };
    int m_thumbRadius = 8;

    float m_min = 0;
    float m_max = 100;
    float m_value = 50;
};
