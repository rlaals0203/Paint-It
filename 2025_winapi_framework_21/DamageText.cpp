#include "pch.h"
#include "DamageText.h"
#include "SceneManager.h"

DamageText::DamageText() :
    m_lifeTime(1.0f),
    m_speed(30.f) {
}

DamageText::~DamageText()
{
}

void DamageText::Init(std::wstring dmg, Vec2 pos)
{
    m_text = dmg;
    SetPos(pos);
    GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::EFFECT);
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
    SetTextColor(_hdc, RGB(255, 255, 255));
    TextOut(_hdc, (int)pos.x, (int)pos.y,
        m_text.c_str(), (int)m_text.length());
}
