#pragma once
#include "BossPattern.h"

class TestPattern :
    public BossPattern
{
public:
    TestPattern(BossController* _controller);
    ~TestPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    float m_cooldownTimer;
    float m_cooldown;
};

