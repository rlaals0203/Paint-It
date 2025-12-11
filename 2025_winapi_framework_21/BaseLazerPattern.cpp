#include "pch.h"
#include "BaseLazerPattern.h"
#include "SceneManager.h"

BaseLazerPattern::BaseLazerPattern(BossController* _controller, int _count, bool _isAwaken,
    float _delay, float _deleteTime)
    : BossPattern(_controller),
    m_delay(_delay),
    m_deleteTime(_deleteTime),
    m_remainCount(_count),
    m_count(_count)
{
    m_penType = _isAwaken ? PenType::LAZER2 : PenType::LAZER;
    m_brushType = _isAwaken ? BrushType::LAZER2 : BrushType::LAZER;
    m_remainDeleteTime = _deleteTime;
}

BaseLazerPattern::~BaseLazerPattern()
{
    while (!m_lasers.empty())
    {
        auto* laser = m_lasers.front();
        m_lasers.pop();
        if (laser && !laser->GetIsDead()) {
            laser->SetDead();
            GET_SINGLE(SceneManager)->RequestDestroy(laser);
        }
    }
}

void BaseLazerPattern::Update()
{
    if (m_lasers.size() > 0)
    {
        m_remainDeleteTime -= fDT;
        if (m_remainDeleteTime <= 0.f) {
            auto* laser = m_lasers.front();
            m_lasers.pop();
            laser->HideLine();
            m_remainDeleteTime = m_deleteTime;
        }
    }

    if (m_remainCount == 0 && m_lasers.size() == 0)
        m_isUsed = false;
}

void BaseLazerPattern::SetUsed()
{
    m_remainTime = m_delay;
    m_remainCount = m_count;
    BossPattern::SetUsed();
}