#pragma once
#include "BossPattern.h"
class SmashPattern :
    public BossPattern
{
public:
    SmashPattern();
    ~SmashPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:

};

