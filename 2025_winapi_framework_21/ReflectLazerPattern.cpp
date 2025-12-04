#include "pch.h"
#include "ReflectLazerPattern.h"
#include "BossController.h"

ReflectLazerPattern::ReflectLazerPattern(BossController* _controller, int _count)
 : BossPattern(_controller), m_isFirst(true)
{
    m_originCount = _count;
}

ReflectLazerPattern::~ReflectLazerPattern()
{
}

void ReflectLazerPattern::Update()
{
    m_time -= fDT;
    if (m_time <= 0.f && m_count > 0)
    {
        if (m_isFirst)
        {
            m_prevPos = m_Controller->GetOwner()->GetPos();
            m_prevAngle = Random::Range(25, 150);
            m_isFirst = false;
        }

        auto* laser = new LaserObject();
        laser->InitLaser(m_prevPos, m_prevAngle, m_duration, 0.25f);
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
        float angleOffset = Random::Range(0, 15);
        float angle = angleOffset + atan2f(reflectDir.y, reflectDir.x) * 180.f / PI;

        m_prevPos = hit;
        m_prevAngle = angle;

        m_count--;
        m_time = m_duration;
    }

    if (m_lasers.size() > 0)
    {
        m_deleteTime -= fDT;
        if (m_deleteTime <= 0.f) {
            auto* laser = m_lasers.front();
            m_lasers.pop();
            laser->HideLine();
            m_deleteTime = m_duration;
        }
    }

    if (m_count == 0 && m_lasers.size() == 0)
        m_isUsed = false;
}

void ReflectLazerPattern::SetUsed()
{
	m_time  = m_duration;
    m_count = m_originCount;
    m_deleteTime = 0.5f;
	BossPattern::SetUsed();
}
