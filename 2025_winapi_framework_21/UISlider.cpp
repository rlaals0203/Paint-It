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
        POINT pt = GET_MOUSEPOS;
        OnMouseDrag(pt);
    }
}

void UISlider::Render(HDC hdc)
{
    Vector2 pos = GetPos();
    Vector2 size = GetSize();

    int trackHeight = (int)(size.y * 0.3f);
    //int centerX = (int)(pos.x + size.x * 0.5f);
    int centerY = (int)(pos.y + size.y * 0.5f);

    m_trackRect = {
        (LONG)pos.x,
        (LONG)(centerY - trackHeight / 2),
        (LONG)(pos.x + size.x),
        (LONG)(centerY + trackHeight / 2)
    };

    if (m_trackTex)
    {
        //todo : 텍스처 그리기 구현
    }
    else
    {
        HBRUSH brush = CreateSolidBrush(RGB(180, 180, 180));
        FillRect(hdc, &m_trackRect, brush);
        DeleteObject(brush);
    }

    int thumbX = PosFromValue(m_value);
    int thumbY = centerY;

    RECT fillRect = { m_trackRect.left, m_trackRect.top, thumbX, m_trackRect.bottom };
    HBRUSH fbrush = CreateSolidBrush(m_fillColor);
    FillRect(hdc, &fillRect, fbrush);
    DeleteObject(fbrush);

    if (m_thumbTex)
    {
        //todo : 텍스처 그리기 구현
    }
    else
    {
        HBRUSH brush = CreateSolidBrush(RGB(50, 150, 250));
        HBRUSH old = (HBRUSH)SelectObject(hdc, brush);
        Ellipse(hdc, thumbX - m_thumbRadius, thumbY - m_thumbRadius, thumbX + m_thumbRadius, thumbY + m_thumbRadius);
        SelectObject(hdc, old);
        DeleteObject(brush);
    }
}

void UISlider::OnMouseClick()
{
    POINT pt = GET_MOUSEPOS;
    float old = m_value;
    m_value = ValueFromPos(pt.x);
    if (m_value != old && m_callback)
    {
        m_callback(m_value);
    }
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
    Vector2 pos = GetPos();
    Vector2 size = GetSize();

    POINT raw = GET_MOUSEPOS;
    Vec2 mouse = Vec2(raw);

    int trackHeight = (int)(size.y * 0.3f);
    int cx = (int)(pos.x + size.x * 0.5f);
    int cy = (int)(pos.y + size.y * 0.5f);

    RECT trackRect = {
        (LONG)pos.x,
        (LONG)(cy - trackHeight / 2),
        (LONG)(pos.x + size.x),
        (LONG)(cy + trackHeight / 2)
    };

    int thumbX = PosFromValue(m_value);
    int thumbY = cy;

    RECT thumbRect = {
        thumbX - m_thumbRadius,
        thumbY - m_thumbRadius,
        thumbX + m_thumbRadius,
        thumbY + m_thumbRadius
    };

    bool was = m_isMouseOver;
    bool overTrack = (mouse.x >= trackRect.left && mouse.x <= trackRect.right && mouse.y >= trackRect.top && mouse.y <= trackRect.bottom);
    bool overThumb = (mouse.x >= thumbRect.left && mouse.x <= thumbRect.right && mouse.y >= thumbRect.top && mouse.y <= thumbRect.bottom);

    m_isMouseOver = overTrack || overThumb;

    if (!was && m_isMouseOver)
    {
        OnMouseEnter();
        SetUIState(UIState::HOVER);
    }
    else if (was && !m_isMouseOver)
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
            m_dragging = true; 
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
    if (m_value != old && m_callback)
    {
        m_callback(m_value);
    }
}
