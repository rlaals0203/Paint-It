#pragma once
#include "BaseLazerPattern.h"


class LaserObject;
class AroundLaserPattern :
    public BaseLazerPattern
{
public:
    AroundLaserPattern(BossController* _controller, int _count, bool _isAwaken = false, float _delay = 0.07f, float _deleteTime = 1.f);
    ~AroundLaserPattern();
public:
    void Update() override;
    void SetUsed() override;
private:
    void MakeLaser();
};

