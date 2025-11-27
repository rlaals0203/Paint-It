#include "pch.h"
#include "UISlider.h"
#include "Texture.h"
#include "InputManager.h"

UISlider::UISlider()
{
}

UISlider::~UISlider()
{
}

void UISlider::Update()
{
    CheckMouseOver();

    if (m_dragging)
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(GetActiveWindow(), &pt);
        OnMouseDrag(pt);
    }
}

void UISlider::Render(HDC hdc)
{
    Vector2 pos = GetPos();
    Vector2 size = GetSize();

    m_trackRect = {
        (LONG)pos.x,
        (LONG)(pos.y + size.y / 2 - 5),
        (LONG)(pos.x + size.x),
        (LONG)(pos.y + size.y / 2 + 5)
    };

    if (m_trackTex)
    {
        // todo: ·»´õ¸µ ±¸Çö
    }
    else
    {
        HBRUSH brush = CreateSolidBrush(RGB(180, 180, 180));
        FillRect(hdc, &m_trackRect, brush);
        DeleteObject(brush);
    }

    int thumbX = PosFromValue(m_value);
    int thumbY = pos.y + size.y / 2;

    if (m_thumbTex)
    {
        // todo: ·»´õ¸µ ±¸Çö
    }
    else
    {
        HBRUSH brush = CreateSolidBrush(RGB(50, 150, 250));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

        Ellipse(hdc,
            thumbX - m_thumbRadius,
            thumbY - m_thumbRadius,
            thumbX + m_thumbRadius,
            thumbY + m_thumbRadius);

        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
    }
}

void UISlider::OnMouseClick()
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(GetActiveWindow(), &pt);

    float old = m_value;
    m_value = ValueFromPos(pt.x);
    if (m_value != old && m_callback) m_callback(m_value);
}


void UISlider::OnMouseDown()
{
    m_dragging = true;
}

void UISlider::OnMouseUp()
{
    m_dragging = false;
}

void UISlider::OnMouseDrag(POINT pt)
{
    float old = m_value;
    m_value = ValueFromPos(pt.x);
    if (m_value != old && m_callback) m_callback(m_value);
}


void UISlider::CheckMouseOver()
{
    Vec2 pos = GetPos();
    Vec2 size = GetSize();

    POINT rawMousePos = GET_MOUSEPOS;
    Vec2 mousePos = Vec2(rawMousePos);

    RECT trackRect = {
        (LONG)pos.x,
        (LONG)(pos.y + size.y / 2 - 5),
        (LONG)(pos.x + size.x),
        (LONG)(pos.y + size.y / 2 + 5)
    };

    int thumbX = PosFromValue(m_value);
    int thumbY = pos.y + size.y / 2;

    int radius = m_thumbRadius;
    RECT thumbRect = {
        thumbX - radius,
        thumbY - radius,
        thumbX + radius,
        thumbY + radius
    };

    bool wasMouseOver = m_isMouseOver;

    bool overTrack =
        (mousePos.x >= trackRect.left && mousePos.x <= trackRect.right &&
            mousePos.y >= trackRect.top && mousePos.y <= trackRect.bottom);

    bool overThumb =
        (mousePos.x >= thumbRect.left && mousePos.x <= thumbRect.right &&
            mousePos.y >= thumbRect.top && mousePos.y <= thumbRect.bottom);

    m_isMouseOver = overTrack || overThumb;

    if (!wasMouseOver && m_isMouseOver)
    {
        OnMouseEnter();
        SetUIState(UIState::HOVER);
    }
    else if (wasMouseOver && !m_isMouseOver)
    {
        OnMouseExit();
        SetUIState(UIState::NORMAL);
    }
    if (!m_dragging && m_isMouseOver && GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON))
    {
        if (overThumb)
        {
            OnMouseDown();
        }
        else if (overTrack)
        {
            OnMouseClick();
        }
    }
    else if (m_dragging && GET_SINGLE(InputManager)->IsUp(KEY_TYPE::LBUTTON))
    {
        OnMouseUp();
    }
}


float UISlider::ValueFromPos(int x)
{
    float ratio = float(x - m_trackRect.left) / float(m_trackRect.right - m_trackRect.left);
    ratio = std::max(0.0f, std::min(1.0f, ratio));
    return m_min + ratio * (m_max - m_min);
}

int UISlider::PosFromValue(float value)
{
    float ratio = (value - m_min) / (m_max - m_min);
    return int(m_trackRect.left + ratio * (m_trackRect.right - m_trackRect.left));
}

void UISlider::SetValue(float value)
{
    float old = m_value;
    m_value = std::max(m_min, std::min(m_max, value));
    if (m_value != old && m_callback) m_callback(m_value);
}
