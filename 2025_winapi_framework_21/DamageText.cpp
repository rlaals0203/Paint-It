#include "pch.h"
#include "DamageText.h"

DamageText::DamageText() :
    m_damage(0),
    m_lifeTime(1.0f),
    m_speed(30.f) {
}

DamageText::~DamageText()
{
}

void DamageText::Init(int dmg, Vec2 pos)
{
    m_damage = dmg;
    SetPos(pos);
}

void DamageText::Update()
{
    m_lifeTime -= fDT;
    if (m_lifeTime <= 0.f)
    {
        SetDead();
    }

    Translate({ 0.f, -m_speed * fDT });
}

void DamageText::Render(HDC _hdc)
{
    Vec2 pos = GetPos();

    wchar_t buf[32];
    swprintf_s(buf, L"%d", m_damage);
    SetTextColor(_hdc, RGB(255, 255, 255));
    TextOut(_hdc, (int)pos.x, (int)pos.y, buf, wcslen(buf));
}
