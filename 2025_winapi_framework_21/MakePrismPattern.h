#pragma once
#include "BossPattern.h";

class MakePrismPattern :
    public BossPattern
{
public:
    MakePrismPattern(BossController* _controller);
    ~MakePrismPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
};

