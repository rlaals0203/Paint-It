#pragma once
#include "BossPattern.h"
#include "BossPattern.h"
class LineProjectilePattern :
    public BossPattern
{
public:
    LineProjectilePattern(BossController* _controller);
    ~LineProjectilePattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
};

