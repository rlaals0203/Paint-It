#pragma once
#include "BaseLazerPattern.h"
#include "LaserObject.h"

class LazerPattern :
    public BaseLazerPattern
{
public:
    LazerPattern(BossController* _controller, int _count, bool _isAwaken = false, float _delay = 0.f, float _deleteTime = 2.f);
    ~LazerPattern();
public:
    virtual void Update() override;
    virtual void SetUsed() override;
private:
    float m_angle;
};

