#include "pch.h"
#include "UIBossHP.h"
#include "EntityHealth.h"
#include "Texture.h"

UIBossHP::UIBossHP()
    :bossHealthCompo(nullptr)
    , m_barTexture(nullptr)
    , m_filledTexture(nullptr)
{
}

UIBossHP::~UIBossHP()
{
}

void UIBossHP::Render(HDC _hdc)
{
    if (!bossHealthCompo)
        return;

    Vec2 pos = GetPos();
    Vec2 size = GetSize();

    int currentHp = bossHealthCompo->GetCurrentHp();
    int maxHP = bossHealthCompo->GetMaxHp();

    pos.y -= 35;
    int barWidth = size.x;
    int barHeight = size.y;

    float ratio = (float)currentHp / (float)maxHP;
    if (ratio < 0.f) ratio = 0.f;

    if (m_barTexture)
    {
        Vec2 pos = GetPos();
        Vec2 size = GetSize();

        int width = m_barTexture->GetWidth();
        int height = m_barTexture->GetHeight();

        TransparentBlt(_hdc,
            pos.x, pos.y,
            barWidth, barHeight,
            m_barTexture->GetTextureDC(),
            0, 0,
            width, height,
            RGB(255, 0, 255));
    }
    else
    {
        RECT_RENDER(_hdc, pos.x, pos.y, barWidth, barHeight);   
    }

    int filledWidth = (int)(barWidth * ratio);
    
    if (m_filledTexture)
    {
        int width = m_filledTexture->GetWidth();
        int height = m_filledTexture->GetHeight();

        TransparentBlt(_hdc,
            pos.x - (barWidth - filledWidth) * 0.5f,
            pos.y,
            filledWidth,
            barHeight,
            m_filledTexture->GetTextureDC(),
            0, 0,
            width, height,
            RGB(255, 0, 255));
    }
    else
    {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, hBrush);
        RECT_RENDER(_hdc,
            pos.x - (barWidth - filledWidth) * 0.5f, pos.y,
            filledWidth, barHeight);

        SelectObject(_hdc, oldBrush);
        DeleteObject(hBrush);
    }
    UIElement::Render(_hdc);
    //UIText::Render(_hdc);
}
