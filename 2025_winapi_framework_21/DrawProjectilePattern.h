#pragma once
#include "BossPattern.h"
class DrawProjectilePattern :
    public BossPattern
{
public:
    DrawProjectilePattern(BossController* _controller, float _delay);
    ~DrawProjectilePattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    float m_delay;
    float m_time;
};

