#include "pch.h"
#include "UIBossHP.h"
#include "EntityHealth.h"

UIBossHP::UIBossHP()
    :bossHealthCompo(nullptr)
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

    RECT_RENDER(_hdc, pos.x, pos.y, barWidth, barHeight);
    int filledWidth = (int)(barWidth * ratio);

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, hBrush);

    RECT_RENDER(_hdc,
        pos.x - (barWidth - filledWidth) * 0.5f, pos.y,
        filledWidth, barHeight);

    SelectObject(_hdc, oldBrush);
    DeleteObject(hBrush);
}
