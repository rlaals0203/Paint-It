#include "pch.h"
#include "LaserObject.h"
#include "Ease.h"
#include "SceneManager.h"
#include "ImpulseManager.h"
#include "DangerGizmo.h"
#include "RotateRender.h"
#include "EntityHealth.h"
#include "DamageText.h"
#include "Scene.h"
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

    GET_SINGLE(SceneManager)->GetCurScene()->RequestSpawn(this, Layer::BACKDAMAGEABLE);
}

LaserObject:: ~LaserObject() {}

void LaserObject::Update()
{
    m_delay -= fDT;
    m_collider->SetSize(GetSize());

    if (m_tickTimer > 0.f)
        m_tickTimer -= fDT;

    if (m_delay <= 0.f && m_isDelay)
    {
        m_dotweenCompo->DOScaleX(m_length, m_duration, EaseInExpo);

        m_isDelay = false;
        GET_SINGLE(ImpulseManager)->ApplyImpulse(8.f, m_duration);
        GET_SINGLE(ResourceManager)->Play(L"laser");
    }
}

void LaserObject::Render(HDC _hdc)
{
    GDISelector pen(_hdc, m_penType);
    GDISelector brush(_hdc, m_brushType);
    Vec2 pos = GetPos();
    Vec2 size = GetSize();

    float halfLen = size.x * 0.5f;
    Vec2 renderOffset = m_dir * halfLen;
    pos = pos + renderOffset;
    RotateRender::RotateRectRender(_hdc, pos, size, m_angle);
    ComponentRender(_hdc);
}

void LaserObject::EnterCollision(Collider* _other)
{
    auto* health = _other->GetOwner()->GetComponent<EntityHealth>();
    if (health)
    {
        health->ApplyDamage(m_damagePerTick);
        m_tickTimer = m_tickInterval;
    }
}

void LaserObject::StayCollision(Collider* _other)
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

void LaserObject::InitLaser(Vec2 _start, float _angle, float _duration, float _delay)
{
    m_angle = _angle;
    m_pos = _start;
    m_duration = _duration;
    m_delay = _delay;

    SetRotation(m_angle);
    SetLine();
}

void LaserObject::SetLine()
{
    m_dir = Vec2(cosf(m_angle * PI / 180.f), sinf(m_angle * PI / 180.f));
    m_dir.Normalize();
    SetPos(m_pos);
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

    if (GetIsDead()) return;
    m_collider->SetActive(false);
    m_dotweenCompo->DOScaleY(0.f, 0.3f, EaseInBack, [this]() 
        {
            SetDead(); 
            GET_SINGLE(SceneManager)->RequestDestroy(this);
        });
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
    if (angleInDegrees < 0)
        angleInDegrees += 360.f;

    InitLaser(_start, angleInDegrees, _duration, _delay);
}

Vec2 LaserObject::GetLaserHitPoint()
{
    Vec2 start = GetPos();
    Vec2 dir = m_dir;
    float x, y, t;

    if (dir.x > 0)
        x = (WINDOW_WIDTH - start.x) / dir.x;
    else
        x = (0 - start.x) / dir.x;

    if (dir.y > 0)
        y = (WINDOW_HEIGHT - start.y) / dir.y;
    else
        y = (0 - start.y) / dir.y;

    t = (x < y) ? x : y;
    return start + dir * t;
}