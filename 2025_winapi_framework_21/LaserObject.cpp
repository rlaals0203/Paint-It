#include "pch.h"
#include "LaserObject.h"
#include "Ease.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ImpulseManager.h"
#include "DangerGizmo.h"
#include "RotateRender.h"
#include "EntityHealth.h"
#include "DamageText.h"
#include "ResourceManager.h"

LaserObject::LaserObject() :
    m_pos({}),
    m_isDelay(true),
    m_length(2000.f),
    m_delay(1.f),
    m_width(15.f),
    m_penType(PenType::LAZER),
    m_brushType(BrushType::LAZER),
    m_damagePerTick(1.f),
    m_tickInterval(0.1f),
    m_tickTimer(0.f)
{
    m_dotweenCompo = AddComponent<DOTweenCompo>();
    m_collider = AddComponent<Collider>();
    SetDestroyOnComplete();

    GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::ENEMYOBSTACLE);
}

LaserObject:: ~LaserObject() {}

void LaserObject::Update()
{
    m_delay -= fDT;
    m_collider->SetSize(GetSize());

    if (m_tickTimer > 0.f)
        m_tickTimer -= fDT;

    if (m_delay <= 0.f)
    {
        m_isDelay = false;
    }
}

void LaserObject::Render(HDC _hdc)
{
    if (m_isDelay)
    {
        // 딜레이 중일 때 (예고선 등)
    }
    else
    {
        SetLine();
        RotateRender::RotateRectRender(_hdc, GetPos() + m_collider->GetOffSetPos(), GetSize(), m_angle);
    }
    ComponentRender(_hdc);
}

void LaserObject::EnterCollision(Collider* _other)
{
    if (m_isDelay) return;
    if (_other->GetName() == L"Player")
    {
        auto* health = _other->GetOwner()->GetComponent<EntityHealth>();
        if (health)
        {
            health->ApplyDamage(m_damagePerTick);
            m_tickTimer = m_tickInterval;
        }
    }
}

void LaserObject::StayCollision(Collider* _other)
{
    if (m_isDelay) return;
    if (_other->GetName() == L"Player")
    {
        if (m_tickTimer <= 0.f)
        {
            auto* health = _other->GetOwner()->GetComponent<EntityHealth>();
            if (health)
            {
                health->ApplyDamage(m_damagePerTick);
                m_tickTimer = m_tickInterval;
            }
        }
    }
}

void LaserObject::InitLaser(Vec2 _start, float _angle, float _duration, float _delay)
{
    SetPos(_start);
    m_angle = _angle;
    m_delay = _delay;

    Vec2 dir = { cosf(_angle * PI / 180.f), sinf(_angle * PI / 180.f) };
    dir.Normalize();
    m_dir = dir;

    SetSize({ 0.f, m_width });

    Vec2 finalOffset = m_dir * (m_length * 0.5f);
    Vec2 finalSize = { m_length, m_width };
    Vec2 finalPos = m_pos + finalOffset;

    m_collider->SetOffSetPos(finalOffset);
    m_collider->SetRotation(m_angle);
    ShowDangerGizmo(finalPos, finalSize);
}

void LaserObject::HideLine()
{
    if (!m_dotweenCompo)
        m_dotweenCompo = AddComponent<DOTweenCompo>();

    m_collider->SetActive(false);
    m_dotweenCompo->DOScaleY(0.f, 0.3f, EaseInBack, [this]() {SetDead(); });
}

void LaserObject::ShowDangerGizmo(Vec2 finalPos, Vec2 finalSize)
{
    auto* dangerGizmo = new DangerGizmo();
    dangerGizmo->SetDangerGizmo(finalPos, finalSize, m_angle, m_delay);
}

void LaserObject::ConnectLaser(Vec2 _start, Vec2 _end, float _duration, float _delay)
{
    Vec2 dir = _end - _start;
    SetLength(dir.Length());
    dir.Normalize();
    float angleInDegrees = atan2(dir.y, dir.x) * 180.f / PI;
    if (angleInDegrees < 0) angleInDegrees += 360.f;

    InitLaser(_start, angleInDegrees, _duration, _delay);
}

Vec2 LaserObject::GetLaserHitPoint()
{
    return m_pos + m_dir * m_length;
}

void LaserObject::SetLine()
{
    SetSize({ m_length, m_width });
}