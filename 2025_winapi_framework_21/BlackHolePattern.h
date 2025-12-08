#pragma once
#include "BossPattern.h"
class BlackHolePattern :
    public BossPattern
{
public:
    BlackHolePattern(BossController* _controller, int count);
    ~BlackHolePattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    Vec2 GetRandomOutsidePos();
private:
    int m_count;
    int m_currentCount;
    float m_remainDelay;
    float m_delay;
};

