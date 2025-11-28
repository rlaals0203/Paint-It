#pragma once
#include "BossPattern.h"

class FallingPattern :
    public BossPattern
{
public:
    FallingPattern(BossController* _controller);
    ~FallingPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    float m_count;
    float m_originCount;
};

