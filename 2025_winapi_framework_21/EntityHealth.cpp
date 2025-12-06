#include "pch.h"
#include "EntityHealth.h"
#include "Object.h"
#include "DamageText.h"

EntityHealth::EntityHealth() : 
	m_maxHp(0), 
    m_isBoss(true),
	m_currentHp(0) { }

EntityHealth::~EntityHealth() { }

void EntityHealth::Init()
{
}

void EntityHealth::LateUpdate()
{
	Object* owner = GetOwner();
}

void EntityHealth::Render(HDC _hdc)
{
    if (m_isBoss) return;
    Object* owner = GetOwner();
    Vec2 pos = owner->GetPos();

    pos.y -= 35;
    int barWidth = 50;
    int barHeight = 6;

    float ratio = (float)m_currentHp / (float)m_maxHp;
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

void EntityHealth::ApplyDamage(int _damage, bool _isDamageText)
{
    if (m_isActive == false) return;
	m_currentHp -= _damage;
	Object* owner = GetOwner();
	owner->OnHit();

    if (_isDamageText)
    {
        DamageText* dmgText = new DamageText();
        dmgText->Init(std::to_wstring(_damage), GetOwner()->GetPos());
    }

	if (m_currentHp <= 0.f)
	{
        if (m_callback != nullptr)
        {
            m_callback();
            m_callback = nullptr;
        }

        if (m_isBoss == false)
        {
            //GET_SINGLE(SceneManager)->LoadScene(L"GameOverScene");
        }

		owner->SetDead();
	}
}
