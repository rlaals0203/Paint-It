#include "pch.h"
#include "ReflectLazerPattern.h"
#include "BossController.h"

ReflectLazerPattern::ReflectLazerPattern(BossController* _controller, int _count, bool _isAwaken, float _delay, float _deleteTime)
    : BaseLazerPattern(_controller, _count, _isAwaken, _delay, _deleteTime) {
    m_startDeleteTime = _deleteTime;
    SetDeleteTime(_delay);
}

ReflectLazerPattern::~ReflectLazerPattern()
{
}

void ReflectLazerPattern::Update()
{
    m_remainTime -= fDT;
    if (m_remainTime <= 0.f && m_remainCount > 0)
    {
        if (m_isFirst) {
            m_prevPos = m_Controller->GetOwner()->GetPos();
            m_prevAngle = Random::Range(25, 150);
            m_isFirst = false;
        }

        auto* laser = new LaserObject();
        laser->SetColor(m_penType, m_brushType);
        laser->InitLaser(m_prevPos, m_prevAngle, m_delay, 0.25f);
        m_lasers.push(laser);

        Vec2 hit = laser->GetLaserHitPoint();
        Vec2 dir = laser->GetDirection();
        Vec2 normal;

        if (fabs(hit.x - 0.f) < 1.f)
            normal = Vec2(1.f, 0.f);
        else if (fabs(hit.x - WINDOW_WIDTH) < 1.f)
            normal = Vec2(-1.f, 0.f);
        else if (fabs(hit.y - 0.f) < 1.f)
            normal = Vec2(0.f, 1.f);
        else if (fabs(hit.y - WINDOW_HEIGHT) < 1.f)
            normal = Vec2(0.f, -1.f);

        Vec2 reflectDir = dir - normal * (2.f * dir.Dot(normal));
        float angleOffset = Random::Range(-30, 30);
        float angle = angleOffset + atan2f(reflectDir.y, reflectDir.x) * 180.f / PI;

        m_prevPos = hit;
        m_prevAngle = angle; m_delay;

        m_remainCount--;
        m_remainTime = m_delay;
    }

    BaseLazerPattern::Update();
}

void ReflectLazerPattern::SetUsed()
{
    BaseLazerPattern::SetUsed();
    m_isFirst = true;
    m_remainDeleteTime = m_startDeleteTime;
}
